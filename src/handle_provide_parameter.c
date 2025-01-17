#include "ribbon_plugin.h"

// Handles deposit/depositETH/depositYieldToken
static void handle_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->skip_remaining_params) {
        return;
    }
    copy_parameter(context->deposit_amount, msg->parameter, sizeof(context->deposit_amount));
    context->skip_remaining_params = true;
}

static void handle_initiate_or_instant_withdraw(ethPluginProvideParameter_t *msg,
                                                context_t *context) {
    if (context->skip_remaining_params) {
        return;
    }
    copy_parameter(context->withdraw_shares_amount,
                   msg->parameter,
                   sizeof(context->withdraw_shares_amount));
    context->skip_remaining_params = true;
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DEPOSIT:
        case DEPOSIT_YIELD_TOKEN:
            handle_deposit(msg, context);
            break;
        case INSTANT_WITHDRAW:
        case INITIATE_WITHDRAWAL:
        case INSTANT_WITHDRAW_STETH:
            handle_initiate_or_instant_withdraw(msg, context);
            break;
        case COMPLETE_WITHDRAWAL:
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
