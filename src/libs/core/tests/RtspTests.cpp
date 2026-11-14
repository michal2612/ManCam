#include <gtest/gtest.h>

import coreRtsp;
import coreException;

TEST(RTSP, Parser) {
    std::string_view host;
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::Exception);
    host = "rt";
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::Exception);
    host = "rtsp";
    EXPECT_NO_THROW(core_rtsp::rtspReceiver::validateHostName(host));
}