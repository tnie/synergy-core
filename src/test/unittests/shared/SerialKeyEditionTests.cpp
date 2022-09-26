/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2016 Symless Inc.
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

#define TEST_ENV

#include "shared/SerialKeyEdition.h"
#include "test/global/gtest.h"

TEST(SerialKeyEditionTests, DefaultEditionType_Unregistered)
{
	SerialKeyEdition edition;
	EXPECT_EQ(kUnregistered, edition.getType());
	EXPECT_EQ(SerialKeyEdition::UNREGISTERED, edition.getName());
	EXPECT_EQ("Synergy 1 (UNREGISTERED)", edition.getDisplayName());
	EXPECT_FALSE(edition.isValid());
}

TEST(SerialKeyEditionTests, SetEditionType_edition)
{
	SerialKeyEdition edition;
	edition.setType(kPro);
	EXPECT_EQ(kPro, edition.getType());
	EXPECT_EQ(SerialKeyEdition::PRO, edition.getName());
	EXPECT_EQ("Synergy 1 Pro", edition.getDisplayName());
	EXPECT_TRUE(edition.isValid());
}

TEST(SerialKeyEditionTests, SetEditionType_string)
{
	SerialKeyEdition edition;
	edition.setType(SerialKeyEdition::BASIC);
	EXPECT_EQ(kBasic, edition.getType());
	EXPECT_EQ(SerialKeyEdition::BASIC, edition.getName());
	EXPECT_EQ("Synergy 1 Basic", edition.getDisplayName());
}

TEST(SerialKeyEditionTests, SetEditionBusiness)
{
	SerialKeyEdition edition;
	edition.setType(kBusiness);
	EXPECT_EQ(kBusiness, edition.getType());
	EXPECT_EQ(SerialKeyEdition::BUSINESS, edition.getName());
	EXPECT_EQ("Synergy 1 Business", edition.getDisplayName());
}

TEST(SerialKeyEditionTests, SetEditionBasicChina)
{
    SerialKeyEdition edition;
    edition.setType(kBasic_China);
    EXPECT_EQ(kBasic_China, edition.getType());
    EXPECT_EQ(SerialKeyEdition::BASIC_CHINA, edition.getName());
    EXPECT_EQ("Synergy Chinese", edition.getDisplayName());
    EXPECT_TRUE(edition.isChina());
}

TEST(SerialKeyEditionTests, SetEditionProChina)
{
    SerialKeyEdition edition;
    edition.setType(kPro_China);
    EXPECT_EQ(kPro_China, edition.getType());
    EXPECT_EQ(SerialKeyEdition::PRO_CHINA, edition.getName());
    EXPECT_EQ("Synergy Pro Chinese", edition.getDisplayName());
    EXPECT_TRUE(edition.isChina());
}

TEST(SerialKeyEditionTests, NameConstructor)
{
    SerialKeyEdition edition(SerialKeyEdition::BUSINESS);
    EXPECT_EQ(kBusiness, edition.getType());
    EXPECT_TRUE(edition.isValid());
}

TEST(SerialKeyEditionTests, isValid)
{
    SerialKeyEdition edition;
    edition.setType(Edition::kBasic);
    EXPECT_TRUE(edition.isValid());

    edition.setType(Edition::kBasic_China);
    EXPECT_TRUE(edition.isValid());

    edition.setType(Edition::kBusiness);
    EXPECT_TRUE(edition.isValid());

    edition.setType(Edition::kPro);
    EXPECT_TRUE(edition.isValid());

    edition.setType(Edition::kPro_China);
    EXPECT_TRUE(edition.isValid());

    edition.setType(Edition::kUnregistered);
    EXPECT_FALSE(edition.isValid());
}
