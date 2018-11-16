#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "cos_api.h"
#include "cos_defines.h"
#include "cos_sys_config.h"
#include "json/json.h"

using namespace qcloud_cos;
using namespace std;

string getBucketName(const string& bucket_file);
int getNameAndPath(string &name, string &path);
bool getRegion(string&, const string);
void getLink(const string& bucket_name, const string& region, 
                const string& object_name);

int main(int argc, char *argv[])
{
    // 1. 指定配置文件路径，初始化 CosConfig
    qcloud_cos::CosConfig config("./config.json");
    qcloud_cos::CosAPI cos(config);
    // 2. 构造上传文件的请求
    // std::string bucket_name = "test-1252852472"; // 上传的目的Bucket名称
    // std::string object_name = "2.jpg"; //object_name 即为对象键（Key），是对象在存储桶中的唯一标识。例如，在对象的访问域名 bucket1-1250000000.cos.ap-guangzhou.myqcloud.com/doc1/pic1.jpg 中，对象键为 doc1/pic1.jpg。
    // request的构造函数中需要传入本地文件路径
    cout<<"将图片拖动到这里，点击并回车..."<<endl;
    std::string bucket_name = getBucketName("./bucket.txt");
    std::string object_name;
    std::string path;
    getNameAndPath(object_name, path);
    qcloud_cos::PutObjectByFileReq req(bucket_name, object_name, path);
    req.SetXCosStorageClass("STANDARD_IA"); // 调用Set方法设置元数据或者ACL等
    qcloud_cos::PutObjectByFileResp resp;
    // 3. 调用上传文件接口
    qcloud_cos::CosResult result = cos.PutObject(req, &resp);
    // 4. 处理调用结果
    if (result.IsSucc())
    {
        // 上传文件成功
        std::cout << "Upload successfully!" << std::endl;
        string region;
        getRegion(region, "./config.json");
        // cout<<region<<endl;
        getLink(bucket_name, region, object_name);
        // std::cout << "ResourceAddr=" << result.GetResourceAddr() << std::endl;
    }
    else
    {
        // 上传文件失败，可以调用CosResult的成员函数输出错误信息，比如requestID等
        std::cout << "ErrorInfo=" << result.GetErrorInfo() << std::endl;
        std::cout << "HttpStatus=" << result.GetHttpStatus() << std::endl;
        std::cout << "ErrorCode=" << result.GetErrorCode() << std::endl;
        std::cout << "ErrorMsg=" << result.GetErrorMsg() << std::endl;
        std::cout << "ResourceAddr=" << result.GetResourceAddr() << std::endl;
        std::cout << "XCosRequestId=" << result.GetXCosRequestId() << std::endl;
        std::cout << "XCosTraceId=" << result.GetXCosTraceId() << std::endl;
    }
}

string getBucketName(const string& bucket_file){
    string bucket_name; 
    ifstream infile; 
    infile.open(bucket_file); 
    infile >> bucket_name; 
    // cout << bucket_name << endl;
    infile.close();
    return bucket_name;
}

int getNameAndPath(string &name, string &path)
{
    string text, temp, _name, _path;
    cin >> text;
    // cout<<text<<endl;
    vector<string> results;
    boost::split(results, text, [](char c) { return c == '/'; });
    vector<string>::iterator itemp = results.end() - 1;
    temp = *itemp;
    // results.clear();
    boost::split(results, temp, [](char c) { return c == '\''; });
    _name = results[0];
    // cout << *name << endl;
    boost::split(results, text, [](char c) { return c == '\''; });
    _path = results[1];
    name = _name;
    path = _path;
    return 0;
}

bool getRegion(string& region, const string config_file="./config.json"){
    // string region;
    Json::Value root;
    Json::Reader reader;
    std::ifstream is(config_file.c_str(), std::ios::in);
    if (!is || !is.is_open()) {
        std::cout << "open config file fail " << config_file << std::endl;
        return false;
    }
    if (!reader.parse(is, root, false)) {
        std::cout << "parse config file fail " << config_file << std::endl;
        is.close();
        return false;
    }
    is.close();
    if (root.isMember("Region")){
        region = root["Region"].asString();
    }
    // cout<<region<<endl;
    return true;
}

void getLink(const string& bucket_name, const string& region, 
                const string& object_name){
    string link = "";
    string str[6];
    str[0] = "https://";
    str[1] = bucket_name;
    str[2] = ".cos.";
    str[3] = region;
    str[4] = ".myqcloud.com/";
    str[5] = object_name;
    for(int i=0; i<6; i++){
        link += str[i];
    }
    cout<<endl;
    cout<<"URL: "<<link<<endl;
    cout<<endl;
    cout<<"HTML: "<<"<img src='"+link+"' alt='"+object_name+"' title='"+object_name+"' />"<<endl;
    cout<<endl;
    cout<<"Markdown: "<<"!["+object_name+"]("+link+")"<<endl;
}