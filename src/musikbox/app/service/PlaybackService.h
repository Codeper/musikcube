#pragma once

#include <sigslot/sigslot.h>

#include <cursespp/IMessageTarget.h>

#include <core/library/track/Track.h>
#include <core/playback/Transport.h>

using musik::core::TrackPtr;
using musik::core::audio::Transport;

class PlaybackService : public IMessageTarget, public sigslot::has_slots<> {
    public:
        PlaybackService(Transport& transport);

        virtual bool IsAcceptingMessages() { return true; }
        virtual void ProcessMessage(IMessage &message);

        Transport& GetTransport() { return this->transport; }

        void Start(std::vector<TrackPtr>& tracks, size_t index);
        void Start(size_t index);
        size_t Count() { return this->playlist.size(); }

    private:
        void OnTransportEvent(int eventType, std::string uri);

        Transport& transport;
        std::vector<TrackPtr> playlist;
        size_t index, next;
};