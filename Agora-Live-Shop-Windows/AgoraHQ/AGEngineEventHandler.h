#pragma once

using namespace agora::rtc;
#include "agora_video_source.h"
#include <unordered_map>

class CAGEngineEventHandler :
	public IRtcEngineEventHandler
{
public:
	CAGEngineEventHandler(void);
	~CAGEngineEventHandler(void);

	void SetMsgReceiver(HWND hWnd = NULL);
	HWND GetMsgReceiver() {return m_hMainWnd;};
	void setSEI(const std::string &strSei);
	void setSEI(std::unordered_map<std::string, std::string>& mapJson);

	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
	virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
	virtual void onWarning(int warn, const char* msg);
	virtual void onError(int err, const char* msg);
	virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	
	virtual void onLeaveChannel(const RtcStats& stat);
	virtual void onRtcStats(const RtcStats& stat);
	virtual void onMediaEngineEvent(int evt);

	virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
	virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);

	virtual void onNetworkQuality(int quality);
	virtual void onFirstLocalVideoFrame(int width, int height, int elapsed);
	virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
	virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
	virtual void onUserJoined(uid_t uid, int elapsed);
	virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
	virtual void onUserMuteAudio(uid_t uid, bool muted);
	virtual void onUserMuteVideo(uid_t uid, bool muted);
	virtual void onApiCallExecuted(const char* api, int error);

	virtual void onLocalVideoStats(const LocalVideoStats& stats);
	virtual void onRemoteVideoStats(const RemoteVideoStats& stats);
	virtual void onCameraReady();
	virtual void onVideoStopped();
	virtual void onConnectionLost();
	virtual void onConnectionInterrupted();

	virtual void onUserEnableVideo(uid_t uid, bool enabled);

	virtual void onStartRecordingService(int error);
	virtual void onStopRecordingService(int error);
	virtual void onRefreshRecordingServiceStatus(int status);

	virtual void onSendSEI(char** info, int* len);
	virtual void onReceiveSEI(const char* info, int len);

private:
	HWND		m_hMainWnd;
	std::string m_strSEI;
	bool m_bActive;
	std::unordered_map<std::string, std::string> m_mapTypeToJson;
};
//advertise process callback
class CAgoraVideoSourceEventHandler : public IAgoraVideoSourceEventHandler
{
	//advertise callback
	virtual void onVideoSourceJoinedChannel(agora::rtc::uid_t uid) override;
	virtual void onVideoSourceRequestNewToken() override;
	virtual void onVideoSourceLeaveChannel() override;
	virtual void onVideoSourceExit() override;
};