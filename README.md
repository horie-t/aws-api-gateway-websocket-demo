# aws-api-gateway-websocket-demo

AWS API GatewayでWebSocketを使うデモです

## 動作要件

以下がインストール・セットアップされている必要があります。

* Serverless Framework

## 使用方法

API Gateway、Lambda関数をデプロイします。

```bash
$ serverless deploy
(中略)
Serverless: Checking Stack update progress...
.....................
Serverless: Stack update finished...
Service Information
service: aws-api-gateway-websocket-demo
stage: dev
region: us-east-1
stack: aws-api-gateway-websocket-demo-dev
resources: 25
api keys:
  None
endpoints:
  wss://xxxxxxxxxx.execute-api.us-east-1.amazonaws.com/dev
functions:
  onConnect: aws-api-gateway-websocket-demo-dev-onConnect
  onDiscconect: aws-api-gateway-websocket-demo-dev-onDiscconect
  broadcast: aws-api-gateway-websocket-demo-dev-broadcast
layers:
  None
Serverless: Removing old service artifacts from S3...
```
