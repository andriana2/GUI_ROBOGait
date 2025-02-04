#ifndef HANDLEMSG_H
#define HANDLEMSG_H

#include "utils.h"
#include "header.h"
#include "toJson.h"
#include "NodeManager.h"

using json = nlohmann::json;

class HandleMsg
{
public:
    HandleMsg(NodeManager &nodeManager);
    void handleMsgJson(const json &json_msg);

private:
    void JoystickPosition(const json &json_msg);
    void StateRemoteControlled(const json &json_msg);
    void DeleteMap(const json &json_msg);
    void ChangeMapName(const json &json_msg);
    void SaveMap(const json &json_msg);
    void GoalPose(const json &json_msg);
    void WaypointFollower(const json &json_msg);
    void StateMenu(const json &json_msg);

    NodeManager &nodeManager;
};

#endif // HANDLEMSG_H