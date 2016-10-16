// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0x50;
        pchMessageStart[2] = 0x70;
        pchMessageStart[3] = 0x35;
	vAlertPubKey = ParseHex("0410a18155b4c6159a86f587198ace0da982d37463ea79f1f171c65f48de77b3de9f3141188dd7dab5791dcf1b222ddf05fc4084c02200ee72517742051dd477e3");
        nDefaultPort = 11517;
        nRPCPort = 17515;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
	// CBlock(hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, ver=1, pow_hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199185, nBits=1e0fffff, nNonce=921682, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//   CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//   CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        const char* pszTimestamp = "RideMyCar Launches.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1393221600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1450199185;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1307090;
	hashGenesisBlock = genesis.GetHash();
	nLastPoWBlock    = 5000;

        assert(hashGenesisBlock == uint256("0x00000109e16b692e4ee543c55f51b0e2e13d5709f0cc36752f7805b3d98a8e1c"));
        assert(genesis.hashMerkleRoot == uint256("0x098b1af159c147d4b20cde0d0ecd7b32398da5a51895dc6a6fc8d0b755515bd3"));

	vSeeds.push_back(CDNSSeedData("146.185.146.172", "146.185.146.172"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(61); // R
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(166);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x2f;
        pchMessageStart[3] = 0xdc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0455649fb8a554ae9d5c2999b019d6095c092cdd5e051e38fff6c12f8e83cf57003c66c98acbd4dd911a2741c4efeca3ad0a876140d42f7021fbbc73a0ff65cc85");
        nDefaultPort = 25713;
        nRPCPort = 25712;
        strDataDir = "testnet";
	// CBlock(hash=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, ver=1, pow_hash=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199186, nBits=1f00ffff, nNonce=57246, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
	genesis.nTime  = 1450199185;
	genesis.nNonce = 1307090;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000109e16b692e4ee543c55f51b0e2e13d5709f0cc36752f7805b3d98a8e1c"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(112);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(240);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0x5b;
        pchMessageStart[2] = 0xfb;
        pchMessageStart[3] = 0xaf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 5);
	// CBlock(hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, ver=1, pow_hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199187, nBits=2007ffff, nNonce=33, vtx=1)
  	//   Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//   vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 33;
	genesis.nTime  = 1450199187;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18555;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
