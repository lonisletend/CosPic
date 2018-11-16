#ifndef UTIL_AUTHTOOl_H
#define UTIL_AUTHTOOl_H

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

#include "request/base_req.h"
#include "util/noncopyable.h"

namespace qcloud_cos {

class AuthTool : private NonCopyable {
public:
    /// \brief ����ǩ����������ָ������Ч����(ͨ��CosSysConfig����, Ĭ��60s)ʹ��
    ///
    /// \param secret_id   ������ӵ�е���Ŀ���ʶ�� ID�����������֤
    /// \param secret_key  ������ӵ�е���Ŀ�����Կ
    /// \param http_method http����,��POST/GET/HEAD/PUT��, �����Сд������
    /// \param in_uri      http uri
    /// \param headers     http header�ļ�ֵ��
    /// \param params      http params�ļ�ֵ��
    ///
    /// \return �ַ�����ʽ��ǩ�������ؿմ�����ʧ��
    static std::string Sign(const std::string& secret_id,
                            const std::string& secret_key,
                            const std::string& http_method,
                            const std::string& in_uri,
                            const std::map<std::string, std::string>& headers,
                            const std::map<std::string, std::string>& params);

    /// \brief ����ǩ����������ָ������Ч����ʹ��
    ///
    /// \param secret_id   ������ӵ�е���Ŀ���ʶ�� ID�����������֤
    /// \param secret_key  ������ӵ�е���Ŀ�����Կ
    /// \param http_method http����,��POST/GET/HEAD/PUT��, �����Сд������
    /// \param in_uri      http uri
    /// \param headers     http header�ļ�ֵ��
    /// \param params      http params�ļ�ֵ��
    ///
    /// \return �ַ�����ʽ��ǩ�������ؿմ�����ʧ��
    static std::string Sign(const std::string& secret_id,
                            const std::string& secret_key,
                            const std::string& http_method,
                            const std::string& in_uri,
                            const std::map<std::string, std::string>& headers,
                            const std::map<std::string, std::string>& params,
                            uint64_t start_time_in_s,
                            uint64_t end_time_in_s);

private:
    /// \brief ��params�е����ݣ�תСд������,key����param_list key=value��param_value_list
    /// \param params ����
    /// \param key_encode key�Ƿ����uri����
    /// \param value_encode value�Ƿ����uri����
    /// \param value_lower value�Ƿ�Сд
    /// \param param_list �������б���;�ָ�
    /// \param param_value_list ������ֵ���б�,��&�ָ�
    /// \retval     ��
    static void FillMap(const std::map<std::string,std::string> &params,
                        bool key_encode,
                        bool value_encode,
                        bool value_lower,
                        std::string* param_list,
                        std::string* param_value_list);

    /// \brief �ҳ���Ҫ��Ȩ��ͷ����������,Ŀǰhost conent-type ����x��ͷ�Ķ�Ҫ��Ȩ
    /// \param hedaers ͷ����kv��
    /// \param filted_req_headers ��Ҫ��Ȩ��ͷ��
    /// \retval ��
    static void FilterAndSetSignHeader(const std::map<std::string,std::string>& headers,
                                       std::map<std::string, std::string>* filted_req_headers);
};

} // namespace qcloud_cos

#endif // AUTHTOOL_H
