#include <gtest/gtest.h>

import coreRtsp;
import coreException;

TEST(RTSP, Parser) {
    std::string_view host;
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::Exception);
    host = "rt";
    EXPECT_THROW(core_rtsp::rtspReceiver::validateHostName(host), core_exception::Exception);
    host = "rtsp://Hikvision:guest@173.200.91.70:10554/Streaming/channels/101";
    const auto hostStruct = core_rtsp::rtspReceiver::validateHostName(host);
    EXPECT_EQ(hostStruct.url, host);
    EXPECT_EQ(hostStruct.username, "Hikvision");
    EXPECT_EQ(hostStruct.password, "guest");
}