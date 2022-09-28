/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_TAG "DataShareServiceProxy"

#include "data_share_service_proxy.h"

#include "datashare_log.h"
#include "ishared_result_set.h"
#include "itypes_utils.h"

namespace OHOS::DataShare {
DataShareServiceProxy::DataShareServiceProxy(const sptr<IRemoteObject> &object)
    : IRemoteProxy<IDataShareService>(object)
{
    LOG_INFO("construct");
}

int32_t DataShareServiceProxy::Insert(const std::string &uri, const DataShareValuesBucket &valuesBucket)
{
    LOG_INFO("Insert");
    MessageParcel data;
    if (!data.WriteInterfaceToken(IDataShareService::GetDescriptor())) {
        LOG_ERROR("Write descriptor failed!");
        return DATA_SHARE_ERROR;
    }
    if (!ITypesUtils::Marshal(data, uri, valuesBucket)) {
        LOG_ERROR("Write to message parcel failed!");
        return DATA_SHARE_ERROR;
    }

    MessageParcel reply;
    MessageOption option = { MessageOption::TF_ASYNC };
    if (Remote()->SendRequest(DATA_SHARE_SERVICE_CMD_INSERT, data, reply, option) != 0) {
        LOG_ERROR("send request failed");
        return DATA_SHARE_ERROR;
    }
    return reply.ReadInt32();
}

int32_t DataShareServiceProxy::Update(
    const std::string &uri, const DataSharePredicates &predicate, const DataShareValuesBucket &valuesBucket)
{
    LOG_INFO("Update");
    MessageParcel data;
    if (!data.WriteInterfaceToken(IDataShareService::GetDescriptor())) {
        LOG_ERROR("Write descriptor failed!");
        return DATA_SHARE_ERROR;
    }
    if (!ITypesUtils::Marshal(data, uri, predicate, valuesBucket)) {
        LOG_ERROR("Write to message parcel failed!");
        return DATA_SHARE_ERROR;
    }

    MessageParcel reply;
    MessageOption option = { MessageOption::TF_ASYNC };
    if (Remote()->SendRequest(DATA_SHARE_SERVICE_CMD_UPDATE, data, reply, option) != 0) {
        LOG_ERROR("send request failed");
        return DATA_SHARE_ERROR;
    }
    return reply.ReadInt32();
}

int32_t DataShareServiceProxy::Delete(const std::string &uri, const DataSharePredicates &predicate)
{
    LOG_INFO("Delete");
    MessageParcel data;
    if (!data.WriteInterfaceToken(IDataShareService::GetDescriptor())) {
        LOG_ERROR("Write descriptor failed!");
        return DATA_SHARE_ERROR;
    }
    if (!ITypesUtils::Marshal(data, uri, predicate)) {
        LOG_ERROR("Write to message parcel failed!");
        return DATA_SHARE_ERROR;
    }

    MessageParcel reply;
    MessageOption option = { MessageOption::TF_ASYNC };
    if (Remote()->SendRequest(DATA_SHARE_SERVICE_CMD_DELETE, data, reply, option) != 0) {
        LOG_ERROR("send request failed");
        return DATA_SHARE_ERROR;
    }
    return reply.ReadInt32();
}

std::shared_ptr<DataShareResultSet> DataShareServiceProxy::Query(
    const std::string &uri, const DataSharePredicates &predicates, const std::vector<std::string> &columns)
{
    LOG_INFO("Query");
    MessageParcel data;
    if (!data.WriteInterfaceToken(IDataShareService::GetDescriptor())) {
        LOG_ERROR("WriteInterfaceToken failed");
        return nullptr;
    }

    if (!ITypesUtils::Marshal(data, uri, predicates, columns)) {
        LOG_ERROR("Write to message parcel failed!");
        return nullptr;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t err = Remote()->SendRequest(DATA_SHARE_SERVICE_CMD_QUERY, data, reply, option);
    if (err != NO_ERROR) {
        LOG_ERROR("Query fail to SendRequest. err: %{public}d", err);
        return nullptr;
    }
    LOG_INFO("end successfully.");
    return ISharedResultSet::ReadFromParcel(reply);
}
} // namespace OHOS::DataShare
