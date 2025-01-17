#ifndef SERVICE_READY_STATE_H
#define SERVICE_READY_STATE_H

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
                    /// @brief Client's state when the service is requested and also up
                    /// @note The state is not copyable.
                    class ServiceReadyState : public ClientServiceState
                    {
                    private:
                        std::condition_variable *const mConditionVariable;
                        std::atomic<helper::SdClientState> mNextState;

                        void waitForCountdown();

                    protected:
                        void Deactivate(helper::SdClientState nextState) override;

                    public:
                        /// @brief Constructor
                        /// @param ttlTimer Finite machine state global TTL timer pointer
                        /// @param conditionVariable Condition variable to be notified when the state activated
                        ServiceReadyState(
                            helper::TtlTimer *ttlTimer,
                            std::condition_variable *conditionVariable) noexcept;

                        ServiceReadyState() = delete;
                        ServiceReadyState(const ServiceReadyState &) = delete;
                        ServiceReadyState &operator=(const ServiceReadyState &) = delete;

                        void Activate(helper::SdClientState previousState) override;

                        /// @brief Inform the state that the client's service is not requested anymore
                        /// @note Due to synchronization, the function does NOT cancel the TTL timer.
                        void ServiceNotRequested() noexcept;

                        void ServiceOffered(uint32_t ttl) noexcept override;

                        /// @brief Inform the state that the service has been stopped
                        void ServiceStopped() noexcept;
                    };
                }
            }
        }
    }
}

#endif