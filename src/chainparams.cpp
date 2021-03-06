// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xFB;
        pchMessageStart[1] = 0xB0;
        pchMessageStart[2] = 0xD7;
        pchMessageStart[3] = 0x42;
        nDefaultPort = 65000;
        nRPCPort = 65001;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 300000; //set this to 300000

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "The world will never be the same";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("41423beef09134e03909a67962e0194e77123041784435f61deb649f6bc3f4cef38c4f371967f1a67130b7105cd6a828ea1384df7ba05504e51ec112de5cb0fe554aac") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1395603900;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 3035138;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        /// Don't uncomment these lines in production. This will break -datadir!
//        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
//            if (++genesis.nNonce==0) break;
//            hashGenesisBlock = genesis.GetHash();
//        }

//        printf("%s\n", hashGenesisBlock.ToString().c_str());
//        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
//        printf("%x\n", bnProofOfWorkLimit.GetCompact());
//        genesis.print();
        
        assert(hashGenesisBlock == uint256("0x00000c652e3e36401e45fee3b9935e1d7c17ae4aed7282a9a0a37c0ba11af4fa"));
        assert(genesis.hashMerkleRoot == uint256("0xf902f42ab7238e51a68b15a7219ed5bcd71061e51d1e643a2fa2d0ec91fdfa64"));

        //TODO: FIX THIS TO WHATEVER DOMAINS
        vSeeds.push_back(CDNSSeedData("bonuscoin.net", "bonuscoin.net"));
        vSeeds.push_back(CDNSSeedData("node1.bonuscoin.net", "node1.bonuscoin.net"));
        vSeeds.push_back(CDNSSeedData("node2.bonuscoin.net", "node2.bonuscoin.net"));
        vSeeds.push_back(CDNSSeedData("node3.bonuscoin.net", "node3.bonuscoin.net"));
        vSeeds.push_back(CDNSSeedData("node4.bonuscoin.net", "node4.bonuscoin.net"));
        vSeeds.push_back(CDNSSeedData("node5.bonuscoin.net", "node5.bonuscoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = 0x19; //'B'
        base58Prefixes[SCRIPT_ADDRESS] = 30;
        base58Prefixes[SECRET_KEY] = 224;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xF3;
        pchMessageStart[1] = 0x34;
        pchMessageStart[2] = 0xB3;
        pchMessageStart[3] = 0xD7;
        nDefaultPort = 55534;
        nRPCPort = 55535;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1374901773;
        genesis.nNonce = 1211565;
        
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        /// Don't uncomment these lines in production. This will break -datadir!
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        //printf("%s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();

        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("bonus.test", "test.bonus.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 130;
        base58Prefixes[SCRIPT_ADDRESS] = 30;
        base58Prefixes[SECRET_KEY] = 239;

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
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 3000000;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1395603900;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
        //// debug print
        /// Don't uncomment these lines in production. This will break -datadir!
        //hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("2222%s\n", hashGenesisBlock.ToString().c_str());
        //printf("2222%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();

        // assert(hashGenesisBlock == uint256("0x13d8d31dde96874006da503dd2b63fa68c698dc823334359e417aa3a92f80433"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
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
        //case CChainParams::TESTNET:
        //    pCurrentParams = &testNetParams;
        //    break;
        //case CChainParams::REGTEST:
        //    pCurrentParams = &regTestParams;
        //    break;
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
