#include "ribbon_plugin.h"

void handle_provide_token(ethPluginProvideInfo_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    // Nothing to do here

    msg->result = ETH_PLUGIN_RESULT_OK;
}
