#ifndef _SERVERLIST_H
#define _SERVERLIST_H
#include <string>
#include <boost/unordered/unordered_map.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/signals2.hpp>
#include <boost/asio/io_service.hpp>
#include "ServerItem.h"
#include "serverManager/DistributeAlgorithm.h"
#include "log/LogCommon.h"

typedef size_t hash_t;
using namespace boost;
class ServerList
{
public:
    typedef boost::function<hash_t (const std::string&)> HashFunc;
    typedef signals2::signal<void (const ServerItem::Ptr&)> ServerEvent;

    ServerEvent OnServerAdded;
    ServerEvent OnServerRemoved;

public:
    SERVERMGR_EXPORT ServerList(uint32_t replication = 200);

    SERVERMGR_EXPORT bool Add(const std::string& host,int port,boost::asio::io_service& ioService);
    SERVERMGR_EXPORT bool Remove(const std::string& host,int port);

    SERVERMGR_EXPORT ServerItem::Ptr Get(const std::string& key);
    SERVERMGR_EXPORT ServerItem::Ptr Get(const std::string& host,int port);
    SERVERMGR_EXPORT size_t Count( void );

    SERVERMGR_EXPORT DistributeAlgorithm::Ptr SetDistributeAlgorithm(const DistributeAlgorithm::Ptr& algorithm);
    SERVERMGR_EXPORT HashFunc SetHashAlogrithm(HashFunc hFunc);

    SERVERMGR_EXPORT const boost::unordered_map<std::string,ServerItem::Ptr> Items( void ) const { return mServers; }
private:
    boost::unordered_map<std::string,ServerItem::Ptr> mServers;
    DistributeAlgorithm::Ptr mDistributeAlgorithm;
    HashFunc mHashFunc;
    uint32_t mReplications;
    boost::mutex mMutex;
    Logger mLog;
};
#endif
 
