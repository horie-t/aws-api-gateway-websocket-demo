# aws-api-gateway-websocket-demo

AWS API GatewayでWebSocketを使うデモです

## 動作要件

以下がインストール・セットアップされている必要があります。

* Serverless Framework

## 使用方法

serverless.ymlファイルの以下の`xxxxx.example.com`をユニークな名前に書き換えます。

```yaml
    bucketName: xxxxx.example.com
```

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

上記の`wss://xxxxxxxxxx.execute-api.us-east-1.amazonaws.com/dev`の`xxxxxxxxxx`は変化します。この値で`client`ディレクトリのHTMLファイルの`WebSocket('wss://xxxxxxxxxx.execute-api.us-east-1.amazonaws.com/dev')`の`xxxxxxxxxx`を書き換えます。

書き換え後、HTMLファイルをS3にデプロイします。

```bash
$ serverless client deploy
(中略)
Serverless: Success! Your site should be available at http://xxxxx.example.com.s3-website-us-east-1.amazonaws.com/
```

デプロイしたindex.htmlファイルなどは、`http://xxxxx.example.com.s3-website-us-east-1.amazonaws.com/index.html`などでアクセスできます。
ただし、complete_notification.htmlはHTTPSプロトコルでアクセスしないと動作しないので、CloudFormationなどを使ってHTTPSアクセスできるようにしてください。

