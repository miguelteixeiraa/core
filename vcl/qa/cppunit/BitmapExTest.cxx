/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vcl/bitmapex.hxx>
#include <bitmapwriteaccess.hxx>
#include <svdata.hxx>
#include <salinst.hxx>

namespace
{
class BitmapExTest : public CppUnit::TestFixture
{
    void testGetPixelColor24_8();
    void testGetPixelColor32();

    CPPUNIT_TEST_SUITE(BitmapExTest);
    CPPUNIT_TEST(testGetPixelColor24_8);
    CPPUNIT_TEST(testGetPixelColor32);
    CPPUNIT_TEST_SUITE_END();
};

void BitmapExTest::testGetPixelColor24_8()
{
    Bitmap aBitmap(Size(3, 3), 24);
    {
        BitmapScopedWriteAccess pWriteAccess(aBitmap);
        pWriteAccess->Erase(Color(0x00, 0x00, 0xFF, 0x00));
    }
    AlphaMask aMask(Size(3, 3));
    {
        AlphaScopedWriteAccess pWriteAccess(aMask);
        pWriteAccess->Erase(Color(0x00, 0xAA, 0xAA, 0xAA));
    }

    BitmapEx aBitmapEx(aBitmap, aMask);

    CPPUNIT_ASSERT_EQUAL(Color(0xAA, 0x00, 0xFF, 0x00), aBitmapEx.GetPixelColor(0, 0));
}

void BitmapExTest::testGetPixelColor32()
{
    // Check backend capabilities and return from the test successfully
    // if the backend doesn't support 32-bit bitmap
    auto pBackendCapabilities = ImplGetSVData()->mpDefInst->GetBackendCapabilities();
    if (!pBackendCapabilities->mbSupportsBitmap32)
        return;

    Bitmap aBitmap(Size(3, 3), 32);
    {
        BitmapScopedWriteAccess pWriteAccess(aBitmap);
        pWriteAccess->Erase(Color(0xAA, 0x00, 0xFF, 0x00));
    }

    BitmapEx aBitmapEx(aBitmap);

    CPPUNIT_ASSERT_EQUAL(Color(0xAA, 0x00, 0xFF, 0x00), aBitmapEx.GetPixelColor(0, 0));
}

} // namespace

CPPUNIT_TEST_SUITE_REGISTRATION(BitmapExTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
