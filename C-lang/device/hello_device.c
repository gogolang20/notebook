#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>

#define BUFFER_MAX (64)
#define OK         (0)
#define ERROR      (-1)

struct cdev *gDev;
struct file_operations *gFile;
dev_t devNum;
unsigned int subDevNum = 1;
int reg_major  = 232;
int reg_minor =  0;
char buffer[BUFFER_MAX];
//struct semaphore sema;
spinlock_t count_lock;
int open_count = 0;

int hello_open(struct inode *p, struct file *f)
{
    //down(&sema);
    spin_lock(&count_lock);
    if (open_count >= 1) {
        //up(&sema);
        spin_unlock(&count_lock);
        printk(KERN_INFO "device is busy, hello_open fail");
        return -EBUSY;
    }
    open_count++
    //up(&sema);
    spin_unlock(&count_lock);
    printk(KERN_INFO "hello_open ok");
    return 0;
}

int hello_close(struct inode *inode, struct file *filp)
{
    if (open_count != 1) {
        printk(KERN_INFO "something wrong, hello_close fail");
        return -EFAULT;
    }
    open_count--;
    printk(KERN_INFO "hello_close ok");
    return 0;
}

ssize_t hello_write(struct file *f, const char __user *u, size_t s, loff_t *i)
{
    printk(KERN_INFO "hello_write\n");
    int writelen = 0;
    writelen = BUFFER_MAX>s ? s:BUFFER_MAX;
    if (copy_from_user(buffer, u, writelen)) {
        return -EFAULT;
    }
    return writelen;
}

ssize_t hello_read(struct file *f, char __user *u, size_t s, loff_t *i)
{
    printk(KERN_INFO "hello_read\n");
    int readlen;
    readlen = BUFFER_MAX > s ? s:BUFFER_MAX;
    if (copy_from_user(u, buffer, readlen)) {
        return -EFAULT;
    }
    return readlen;
}

int hello_init(void)
{
    devNum = MKDEV(reg_major, reg_minor);
    if (OK == register_chrdev_region(devNum, subDevNum, "helloworld")) {
        printk(KERN_INFO "register_chrdev_region ok \n");
    } else {
        printk(KERN_INFO "register_chrdev_region error \n");
        return ERROR;
    }
    printk(KERN_INFO "hello driver init \n");
    gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);
    gFile->open = hello_open;
    gFile->release = hello_close;
    gFile->read = hello_read;
    gFile->write = hello_write;
    gFile->owner = THIS_MODULE;
    cdev_init(gDev, gFile);
    cdev_add(gDev, gFile, 1);

    //sema_init(&sema, 1);
    spin_lock_init(&count_lock);
    return 0;
}

void __exit hello_exit(void)
{
    printk(KERN_INFO "hello driver exit \n");
    cdev_del(gDev);
    kfree(gFile);
    kfree(gDev);
    unregister_chrdev_region(devNum, subDevNum);
    return;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GLP");
