## CosPic简介

CosPic是一个Linux下基于[**cos-cpp-sdk-v5**](https://github.com/tencentyun/cos-cpp-sdk-v5)开发的图片上传工具，如果你使用腾讯云对象存储COS的bucket做图床，那么可以使用CosPic一键上传图片至COS并获取相应的链接，目前提供生成URL，HTML以及Markdown格式直接复制使用，让你写博客时更加方便。

PS: 目前只有简单的上传功能，还有很多不完善之处，使用前请仔细阅读注意事项，以免对您造成损失。

## CosPic使用

1. 编译生成cospic可执行文件(build目录中有已经编译好的)

2. 配置文件config.json，格式如下：

   > {
   >     "SecretId":"×××××××××××××××××××××××××××××××",
   >     "SecretKey":"××××××××××××××××××××××××××××××",
   >     "Region":"ap-beijing",
   >     "SignExpiredTime":360,
   >     "ConnectTimeoutInms":6000,
   >     "ReceiveTimeoutInms":5000,
   >     "AsynThreadPoolSize":2,
   >     "UploadPartSize":10485760,
   >     "UploadCopyPartSize":10485760,
   >     "UploadThreadPoolSize":5,
   >     "LogoutType":1,
   >     "LogLevel":3,
   >     "DownloadThreadPoolSize":5,
   >     "DownloadSliceSize":4194304
   > }

   SecretId， SecretKey字段需要自行填入，其他默认就好。

3. bucket.txt, 配置bucket存储桶，格式如下：

   > test-1234567890

4. 终端运行./cospic。

5. 拖动图片到终端，点击并回车。

6. 等待上传（基本不用等^_^）,复制需要的链接。

   ![](https://i.loli.net/2018/11/16/5beeb5d923b87.png)

## 注意事项

- 目前仅提供图片直接上传到bucket，不支持文件夹管理等。
- 目前没有处理上传图片与bucket中存在图片重名情况，可能会覆盖。

## 编译环境

编译环境配置参考[**cos-cpp-sdk-v5**](https://github.com/tencentyun/cos-cpp-sdk-v5) README.md。

