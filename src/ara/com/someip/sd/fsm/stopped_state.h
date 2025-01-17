#ifndef STOPPED_STATE_H
#define STOPPED_STATE_H

#include <atomic>
#include "./client_service_state.h"

namespace ara
{
    namespace com
    {
        namespace someip
        {
            namespace sd
            {
                namespace fsm
                {
                    /// @brief Client state when the service is stopped
                    /// @note The state is not copyable
                    class StoppedState : public ClientServiceState
                    {
                    private:
                        std::condition_variable *const mConditionVariable;
                        std::atomic<helper::SdClientState> mNextState;

                    protected:
                        void Deactivate(helper::SdClientState nextState) override;

                    public:
                        /// @brief Constructor
                        /// @param ttlTimer Finite machine state global TTL timer pointer
                        /// @param conditionVariable Condition variable to be notified when the state activated
                        StoppedState(
                            helper::TtlTimer *ttlTimer,
                            std::condition_variable *conditionVariable) noexcept;

                        StoppedState() = delete;
                        StoppedState(const StoppedState &) = delete;
                        StoppedState &operator=(const StoppedState &) = delete;

                        void Activate(helper::SdClientState previousState) override;

                        /// @brief Inform the state that the client's service is not requested anymore
                        /// @note Due to synchronization, the function does NOT cancel the TTL timer.
                        void ServiceNotRequested();

                        void ServiceOffered(uint32_t ttl) noexcept override;
                    };
                }
            }
        }
    }
}

#endif