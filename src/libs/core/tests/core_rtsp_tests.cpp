#include <gtest/gtest.h>

import core_rtsp;
import core_exception;

TEST(RTSP, Parser) {
    std::string_view host;
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::coreException);
    host = "rt";
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::coreException);
    host = "rtsp";
    EXPECT_NO_THROW(core_rtsp::rtspReceiver::validateHostName(host));
}