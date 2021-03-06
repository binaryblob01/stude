//=============================================================================
// File:       boyermor.cpp
// Contents:   Definitions for DwBoyerMoore
// Maintainer: Doug Sauder <dwsauder@fwb.gulf.net>
// WWW:        http://www.fwb.gulf.net/~dwsauder/mimepp.html
// $Revision: 1.6 $
// $Date: 1997/09/27 11:53:38 $
//
// Copyright (c) 1996, 1997 Douglas W. Sauder
// All rights reserved.
// 
// IN NO EVENT SHALL DOUGLAS W. SAUDER BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
// THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF DOUGLAS W. SAUDER
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// DOUGLAS W. SAUDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
// BASIS, AND DOUGLAS W. SAUDER HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
//=============================================================================

#define DW_IMPLEMENTATION

#include <mimelib/config.h>
#include <mimelib/debug.h>
#include <string.h>
#include <mimelib/boyermor.h>


DwBoyerMoore::DwBoyerMoore(const char* aCstr)
{
    size_t len = strlen(aCstr);
	_Assign(aCstr, len);
}


DwBoyerMoore::DwBoyerMoore(const DwString& aStr)
{
    _Assign(aStr.data(), aStr.length());
}


DwBoyerMoore::~DwBoyerMoore()
{
}


void DwBoyerMoore::Assign(const char* aCstr)
{
    size_t len = strlen(aCstr);
	_Assign(aCstr, len);
}


void DwBoyerMoore::Assign(const DwString& aStr)
{
    _Assign(aStr.data(), aStr.length());
}


void DwBoyerMoore::_Assign(const char* aPat, size_t aPatLen)
{
    mPatLen = aPatLen;
    mPat = new char[mPatLen+1];
    strncpy(mPat, aPat, mPatLen);
    mPat[mPatLen] = 0;
    // Initialize the jump table for Boyer-Moore-Horspool algorithm
    size_t i;
    for (i=0; i < 256; ++i)
        mSkipAmt[i] = (unsigned char) mPatLen;
    for (i=0; i < mPatLen-1; ++i)
        mSkipAmt[(unsigned)mPat[i]] = (unsigned char) (mPatLen - i - 1);
}


size_t DwBoyerMoore::FindIn(const DwString& aStr, size_t aPos)
{
    if (aStr.length() <= aPos) return (size_t)-1;
    size_t bufLen = aStr.length() - aPos;
    const char* buf = aStr.data() + aPos;
    size_t i;
    for (i=mPatLen-1; i < bufLen; i += mSkipAmt[(unsigned char)buf[i]]) {
        int iBuf = i;
        int iPat = mPatLen - 1;
        while (iPat >= 0 && buf[iBuf] == mPat[iPat]) {
            --iBuf;
            --iPat;
        }
        if (iPat == -1)
            return aPos + iBuf + 1;
    }
    return (size_t)-1;
}
