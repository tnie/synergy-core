/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2014-2016 Symless Ltd.
 * 
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 * 
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lib/server/Config.h"
#include "net/XSocket.h"
#include "test/global/gtest.h"

class OnlySystemFilter: public InputFilter::Condition {
    public:
        Condition*        clone() const override {
            return new OnlySystemFilter();
        }
        String            format() const override {
            return "";
        }

        InputFilter::EFilterStatus    match(const Event& ev) override {
            return ev.getType() == Event::kSystem ? InputFilter::kActivate : InputFilter::kNoMatch;
        }
};

TEST(ServerConfigTests, serverconfig_will_deem_inequal_configs_with_different_map_size)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_inequal_configs_with_different_cell_names)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenB");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_equal_configs_with_same_cell_names)
{
    Config a(nullptr);
    Config b(nullptr);
    EXPECT_TRUE(a.addScreen("screenA"));
    EXPECT_TRUE(a.addScreen("screenB"));
    EXPECT_TRUE(a.addScreen("screenC"));
    EXPECT_TRUE(a.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(a.connect("screenB", EDirection::kLeft, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(b.addScreen("screenA"));
    EXPECT_TRUE(b.addScreen("screenB"));
    EXPECT_TRUE(b.addScreen("screenC"));
    EXPECT_TRUE(b.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(b.connect("screenB", EDirection::kLeft, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    a.getInputFilter()->addFilterRule(InputFilter::Rule{new OnlySystemFilter()});
    b.getInputFilter()->addFilterRule(InputFilter::Rule{new OnlySystemFilter()});
    a.addAlias("screenA", "aliasA");
    b.addAlias("screenA", "aliasA");
    NetworkAddress addr1("localhost", 8080);
    addr1.resolve();
    NetworkAddress addr2("localhost", 8080);
    addr2.resolve();
    a.setSynergyAddress(addr1);
    b.setSynergyAddress(addr2);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

TEST(NetworkAddress, hostname_valid_parsing)
{
    const int validPort  = 24900;
    const String portStr = std::to_string(validPort);

    //list of test cases. 1 param - hostname for parsing, 2 param - port, 3 param - expected hostname
    const std::initializer_list<std::tuple<String, int, String>> validTestCases = {
        std::make_tuple(String("127.0.0.1"),                                 validPort, "127.0.0.1"),
        std::make_tuple(String("127.0.0.1:") + portStr,                      0,         "127.0.0.1"),
        std::make_tuple(String("localhost"),                                 validPort, "localhost"),
        std::make_tuple(String("localhost:") + portStr,                      0,         "localhost"),
        std::make_tuple(String(""),                                          validPort, ""),
        std::make_tuple(String(":") + portStr,                               0,         ""),
        //Temporary disabled tests for ipv6
        //std::make_tuple(String("[::1]:") + portStr,                          0,         "::1"),
        //std::make_tuple(String("[fe80::a156:9f36:793:7bfb%14]:") + portStr,  0,         "fe80::a156:9f36:793:7bfb%14"),
        //std::make_tuple(String("::1"),                                       validPort, "::1"),
        //std::make_tuple(String("fe80::a156:9f36:793:7bfb%14"),               validPort, "fe80::a156:9f36:793:7bfb%14"),
        //std::make_tuple(String("fe80:0000:0000:0000:a156:9f36:793:7bfb%14"), validPort, "fe80:0000:0000:0000:a156:9f36:793:7bfb%14"),
    };

    for (const auto &caseParams : validTestCases) {
        NetworkAddress addr(std::get<0>(caseParams), std::get<1>(caseParams));
        addr.resolve();

        EXPECT_TRUE(addr.getHostname() == std::get<2>(caseParams));
        EXPECT_TRUE(addr.getPort() == validPort);
        EXPECT_TRUE(addr.getAddress() != nullptr);
    }

    //list of non valid hostnames
    const std::initializer_list<String> nonValidTestCases = {
        ":nonValidPort",
        ":",
        //Temporary disabled tests for ipv6
        //"[::1]:",
        //"[::1]:nonValidPort",
        //"fe80::1",
        //"[::1]:-1",
        //"[::1]:65536"
    };

    for (const auto &caseParam : nonValidTestCases) {
        bool flag = false;
        try {
            NetworkAddress addr(caseParam, validPort);
        }  catch (const XSocketAddress&) {

            flag = true;
        }

        EXPECT_TRUE(flag);
    }
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_same_cell_names_different_options)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_same_cell_names_different_aliases1)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    b.addAlias("screenA", "aliasA");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_same_cell_names_different_aliases2)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    a.addAlias("screenA", "aliasA");
    b.addAlias("screenA", "aliasB");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_different_global_options)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_different_filters)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    a.getInputFilter()->addFilterRule(InputFilter::Rule{new OnlySystemFilter()});
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_configs_with_different_address)
{
    Config a(nullptr);
    Config b(nullptr);
    a.addScreen("screenA");
    b.addScreen("screenA");
    a.setSynergyAddress(NetworkAddress(8080));
    b.setSynergyAddress(NetworkAddress(1010));
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_cell_neighbours1)
{
    Config a(nullptr);
    Config b(nullptr);
    EXPECT_TRUE(a.addScreen("screenA"));
    EXPECT_TRUE(a.addScreen("screenB"));
    EXPECT_TRUE(a.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(b.addScreen("screenA"));
    EXPECT_TRUE(b.addScreen("screenB"));
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_cell_neighbours2)
{
    Config a(nullptr);
    Config b(nullptr);
    EXPECT_TRUE(a.addScreen("screenA"));
    EXPECT_TRUE(a.addScreen("screenB"));
    EXPECT_TRUE(a.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(b.addScreen("screenA"));
    EXPECT_TRUE(b.addScreen("screenB"));
    EXPECT_TRUE(b.connect("screenA", EDirection::kBottom, 0.0f, 0.25f, "screenB", 0.25f, 1.0f));
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(ServerConfigTests, serverconfig_will_deem_different_cell_neighbours3)
{
    Config a(nullptr);
    Config b(nullptr);
    EXPECT_TRUE(a.addScreen("screenA"));
    EXPECT_TRUE(a.addScreen("screenB"));
    EXPECT_TRUE(a.addScreen("screenC"));
    EXPECT_TRUE(a.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenB", 0.5f, 1.0f));
    EXPECT_TRUE(b.addScreen("screenA"));
    EXPECT_TRUE(b.addScreen("screenB"));
    EXPECT_TRUE(b.addScreen("screenC"));
    EXPECT_TRUE(b.connect("screenA", EDirection::kBottom, 0.0f, 0.5f, "screenC", 0.5f, 1.0f));
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}
