# Geth

私链搭建

```shell
https://github.com/ethereum/go-ethereum

git clone https://github.com/ethereum/go-ethereum.git
cd go-ethereum

#下载后指定到 版本 v1.10.8
git tag
git ckeckout v1.10.8
make geth #编译

./build/bin/geth version #查看版本

cd /root/goproject/src/go-ethereum #go-ethereum 下载到的目录
./build/bin/geth --datadir ./data #--datadir 指定存放数据目录 #演示启动
#go-ethereum/data/keystore 存储的是账号信息
```

搭建步骤

```
1 配置文件 genesis.json
2 初始化
3 启动 + 控制台演示 #支持table键 补齐
4 Json-Rpc 测试
```

1 配置文件 genesis.json

```shell
{
  "config": {
    "chainId": <arbitrary positive integer>,
    "homesteadBlock": 0,
    "eip150Block": 0,
    "eip155Block": 0,
    "eip158Block": 0,
    "byzantiumBlock": 0,
    "constantinopleBlock": 0,
    "petersburgBlock": 0,
    "istanbulBlock": 0,
    "berlinBlock": 0,
    "londonBlock": 0
  },
  "alloc": {
    "0x0000000000000000000000000000000000000001": {
      "balance": "111111111"
    },
    "0x0000000000000000000000000000000000000002": {
      "balance": "222222222"
    }
  },
  "coinbase": "0x0000000000000000000000000000000000000000",
  "difficulty": "0x20000", #2000
  "extraData": "",
  "gasLimit": "0x2fefd8",
  "nonce": "0x0000000000000042",
  "mixhash": "0x0000000000000000000000000000000000000000000000000000000000000000",
  "parentHash": "0x0000000000000000000000000000000000000000000000000000000000000000",
  "timestamp": "0x00"
}
```

```shell
Linux 系统演示

初始化私有链
./geth --datadir /root/goproject/src/go-geth init /root/goproject/src/go-geth/genesis.json

启动+演示
./geth --datadir /root/goproject/src/go-geth --networkid 99 #视频
./geth --datadir /root/goproject/src/go-geth --networkid 99 console #console 启动控制台
./geth --datadir /root/goproject/src/go-geth --networkid 99 console 2>output.log #更简洁
./geth --datadir /root/goproject/src/go-geth --networkid 99 --rpc console 2>output.log #--rpc 8545


> web3 #查看命令提示
> admin
> eth
> personal
> txpool
> miner
> eth.accounts #查询账号
> eth.getBalance("0x0000000000000000000000000000000000000001")
> web3.fromWei(eth.getBalance("0x0000000000000000000000000000000000000001"))
> eth.blockNumber
> personal.newAccount() #创建一个账户
> eth.accounts #再次查看账户 #keystore 文件出现账户信息
["0x10e4d625de99dbda447df7a2d41be58095b30571"]
> eth.accounts[0]
"0x10e4d625de99dbda447df7a2d41be58095b30571"

> eth.getBalance("0x10e4d625de99dbda447df7a2d41be58095b30571") 
> eth.getBalance(eth.accounts[0]) 
```

```shell
> eth.sendTransaction({from: "0x0000000000000000000000000000000000000001", to: eth.accounts[0], value: 10000}) #发送交易
Error: unknown account
    at web3.js:6365:37(47)
    at send (web3.js:5099:62(35))
    at <eval>:1:20(13)
#转账之前需要解锁
> personal.unlockAccount(eth.accounts[0])
Unlock account 0x10e4d625de99dbda447df7a2d41be58095b30571
Passphrase: #输入密码
true

> web3.toWei(10, `ether`)
"10000000000000000000"

> eth.sendTransaction({from: eth.accounts[0], to: "0x0000000000000000000000000000000000000001", value: web3.toWei(10, `ether`)}) 
Error: insufficient funds for transfer #错误:转账资金不足

> miner.start(1) #挖矿
> eth.blockNumber #还是0
> eth.coinbase
> miner.stop()
```

```shell
./geth --datadir /root/goproject/src/go-geth-dev --dev console 2>output.log #开发者模式
> personal.newAccount("123456") #创建账户并指定密码
> eth.getBalance("0xc2e08b6eef9f38ce0aa105542e7fd0a7d6b0229a")
> eth.sendTransaction({from: eth.accounts[0], to: eth.accounts[1], value: web3.toWei(10, `ether`)})
"0x529521aa51372ee9938ccc76c58fbedcf8181953bdca77bfac606b360837b648"
> eth.getBalance("0xc2e08b6eef9f38ce0aa105542e7fd0a7d6b0229a")
10000000000000000000

> eth.getTransaction("0x529521aa51372ee9938ccc76c58fbedcf8181953bdca77bfac606b360837b648")
{
  accessList: [],
  blockHash: "0xbe130df820aabb5c08c3830c01742cc69f4aed5f40ddb7777eb7ca50eefdef13",
  blockNumber: 1,
  chainId: "0x539",
  from: "0x79433cf2605a39d3315fa38c0243cf40c7b68c50",
  gas: 21000,
  gasPrice: 875000001,
  hash: "0x529521aa51372ee9938ccc76c58fbedcf8181953bdca77bfac606b360837b648",
  input: "0x",
  maxFeePerGas: 2000000001,
  maxPriorityFeePerGas: 1,
  nonce: 0,
  r: "0xb0f0999c0fce53ace4ed3678450a3c4d88d7c19807667c32bdff1717c536538a",
  s: "0x5264c27dace641dce0433bfe19b4355d1dd89eae95fda88ab02d0da917edbb24",
  to: "0xc2e08b6eef9f38ce0aa105542e7fd0a7d6b0229a",
  transactionIndex: 0,
  type: "0x2",
  v: "0x0",
  value: 10000000000000000000
}
> eth.getBlockTransactionCount(1)
> eth.getBlock(1)
{
  baseFeePerGas: 875000000,
  difficulty: 2,
  extraData: "0xd883010a10846765746888676f312e31372e35856c696e7578000000000000001e8d1cee02b1010d313cec8ac438fa0893ea5d842a0f0218bbd26bea57961dc073d77243674c1e945463ceafa2d332f87aeb8c36d5f0dc84b5e99f005c5cd6a700",
  gasLimit: 11488771,
  gasUsed: 21000,
  hash: "0xbe130df820aabb5c08c3830c01742cc69f4aed5f40ddb7777eb7ca50eefdef13",
  logsBloom: "0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  miner: "0x0000000000000000000000000000000000000000",
  mixHash: "0x0000000000000000000000000000000000000000000000000000000000000000",
  nonce: "0x0000000000000000",
  number: 1,
  parentHash: "0x845bd0252ccda4df52dcf640378e92048fd8a88425daa7956ec4a93b0519c21c",
  receiptsRoot: "0xf78dfb743fbd92ade140711c8bbc542b5e307f0ab7984eff35d751969fe57efa",
  sha3Uncles: "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
  size: 731,
  stateRoot: "0x873c8ce94501d5180751d3de81761e12180a78156545f56e764439b2c210efa7",
  timestamp: 1642333766,
  totalDifficulty: 3,
  transactions: ["0x529521aa51372ee9938ccc76c58fbedcf8181953bdca77bfac606b360837b648"],
  transactionsRoot: "0x3c416e3a97e48777bab947ea36789a6ccad55101d6db19237bfbf1d8dedc60aa",
  uncles: []
}
```

Json-Rpc 测试

```
./geth --datadir /root/goproject/src/go-geth --networkid 99 console 2>output.log


curl -X POST -H "Content-Type: application/json" --data '{"jsonrpc":"2.0","method":"web3_clientVersion","params": [],"id":1}' http://localhost:8545

127.0.0.1:8545
```

```
创建一个新账号

启动
$ geth --datadir=path/to/custom/data/folder  --mine --metrics --syncmode=full --gcmode=archive --port 30304 --rpc --rpcaddr  0.0.0.0 --rpcport 8545 --rpcapi db,eth,net,web3,personal --allow-insecure-unlock --networkid 99 console

geth --datadir /root/goproject/src/go-geth  --miner.etherbase 0x06a897F9b06821aEE42C9360d2b053e8b0e623f1  --mine --metrics --syncmode=full --gcmode=archive --port 30304 --rpc --rpcaddr  0.0.0.0 --rpcport 8545 --rpcapi db,eth,net,web3,personal --allow-insecure-unlock --networkid 99 console
```

```
Windows:
#genesis.json 放置的位置,带上私链存放数据的路径
.\wormholes.exe  --datadir E:\goproject\src\go-geth  init E:\goproject\src\genesis.json
--datadir 数据存放位置

启动私有链
$ geth --datadir=path/to/custom/data/folder  --mine --metrics --syncmode=full --gcmode=archive --port 30304 --rpc --rpcaddr  0.0.0.0 --rpcport 8545 --rpcapi db,eth,net,web3,personal --allow-insecure-unlock --networkid 98 console

# 添加一个新账户
.\wormholes.exe account new 
$ Public address of the key:   0x06a897F9b06821aEE42C9360d2b053e8b0e623f1
$ Path of the secret key file: C:\Users\andre\AppData\Local\Ethereum\keystore\UTC--2022-01-14T06-47-29.973164500Z--06a897f9b06821aee42c9360d2b053e8b0e623f1

启动
.\wormholes.exe --datadir E:\goproject\src\go-geth  --miner.etherbase 0x06a897F9b06821aEE42C9360d2b053e8b0e623f1  --mine --metrics --syncmode=full --gcmode=archive --port 30304 --rpc --rpcaddr  0.0.0.0 --rpcport 8545 --rpcapi db,eth,net,web3,personal --allow-insecure-unlock --networkid 98 console
```

Json-Rpc 测试

```shell
另开一个终端:
curl -X POST -H "Content-Type: application/json"  --data "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"0x06a897F9b06821aEE42C9360d2b053e8b0e623f1\", \"latest\"],\"id\":98}" 127.0.0.1:8545

curl -X POST -H "Content-Type: application/json"  --data "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getNFTOwner\",\"params\":[\"0x06a897F9b06821aEE42C9360d2b053e8b0e623f1\", \"latest\"],\"id\":98}" 127.0.0.1:8545




curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_sendTransaction","params": [{"from": "0x7778e3250b2402d27BB0E294913Ceed8CAc8C556","to": "0x1196dacfb9ef1b42c4186a81413f7ec5f2eee174","data": "0x776f726d686f6c65733a7b2274797065223a342c226e667461646472657373223a22307837373738653332353062323430326432374242304532393439313343656564384341633843353536222c2276657273696f6e223a2276302e302e31227d"}],"id":20211209}' 127.0.0.1:8545

curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_sendTransaction","params": [{"from": "0x1196dacfb9ef1b42c4186a81413f7ec5f2eee174","to": "0x7778e3250b2402d27BB0E294913Ceed8CAc8C556","data": "0x776f726d686f6c65733a7b2274797065223a342c226e667461646472657373223a22307837373738653332353062323430326432374242304532393439313343656564384341633843353536222c2276657273696f6e223a2276302e302e31227d"}],"id":20211209}' 127.0.0.1:8545

curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_sendTransaction","params": [{"from": "0x7778e3250b2402d27BB0E294913Ceed8CAc8C556","to": "0x7778e3250b2402d27BB0E294913Ceed8CAc8C556","data": "0x776f726d686f6c65733a7b2274797065223a342c226e667461646472657373223a22307837373738653332353062323430326432374242304532393439313343656564384341633843353536222c2276657273696f6e223a2276302e302e31227d"}],"id":20211209}' 127.0.0.1:8545

curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_sendTransaction","params": [{"from": "0x1196dacfb9ef1b42c4186a81413f7ec5f2eee174","to": "0x1196dacfb9ef1b42c4186a81413f7ec5f2eee174","data": "0x776f726d686f6c65733a7b2274797065223a342c226e667461646472657373223a22307837373738653332353062323430326432374242304532393439313343656564384341633843353536222c2276657273696f6e223a2276302e302e31227d"}],"id":20211209}' 127.0.0.1:8545

curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_getBalance","params":["0x06a897F9b06821aEE42C9360d2b053e8b0e623f1", "latest"],"id":98}' 127.0.0.1:8545


curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_getBalance","params":["0x7778e3250b2402d27BB0E294913Ceed8CAc8C556", "latest"],"id":20211209}' 127.0.0.1:8545
curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_getBalance","params":["0xd610c4bfcf109ebac3895a63192151832c32d127", "latest"],"id":20211209}' 127.0.0.1:8545

curl -X POST -H 'Content-Type: application/json' --data '{"jsonrpc":"2.0","method":"eth_getBalance","params":["0xa5D06dF58e5c9Ac128760Cae67BAaa5Bd6406544", "0x17"],"id":48}' 127.0.0.1:8545
```

# Git

```shell
git clone XXX

git branch -a #查看所有分支

git checkout sunchaosheng_dev #切换分支

git log
git tag
git checkout v1.8.17 {分支版本} #切换到指定的版本

git pull origin sunchaosheng_dev #拉取分支代码
```
