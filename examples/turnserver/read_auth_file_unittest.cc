/*
 *  Copyright 2018 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <sstream>  // no-presubmit-check TODO(webrtc:8982)

#include "examples/turnserver/read_auth_file.h"
#include "test/gtest.h"

namespace webrtc_examples {

TEST(ReadAuthFile, HandlesEmptyFile) {
  std::istringstream empty;  // no-presubmit-check TODO(webrtc:8982)
  auto map = ReadAuthFile(&empty);
  EXPECT_TRUE(map.empty());
}

TEST(ReadAuthFile, RecognizesValidUser) {
  std::istringstream  // no-presubmit-check TODO(webrtc:8982)
      file("foo=deadbeaf\n");
  auto map = ReadAuthFile(&file);
  ASSERT_NE(map.find("foo"), map.end());
  EXPECT_EQ(map["foo"], "\xde\xad\xbe\xaf");
}

TEST(ReadAuthFile, EmptyValueForInvalidHex) {
  std::istringstream file(  // no-presubmit-check TODO(webrtc:8982)
      "foo=deadbeaf\n"
      "bar=xxxxinvalidhex\n"
      "baz=cafe\n");
  auto map = ReadAuthFile(&file);
  ASSERT_NE(map.find("foo"), map.end());
  EXPECT_EQ(map["foo"], "\xde\xad\xbe\xaf");
  EXPECT_EQ(map.find("bar"), map.end());
  ASSERT_NE(map.find("baz"), map.end());
  EXPECT_EQ(map["baz"], "\xca\xfe");
}

}  // namespace webrtc_examples
