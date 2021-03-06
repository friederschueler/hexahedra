//---------------------------------------------------------------------------
/// \file   hexa/crypto.cpp
/// \brief  Common cryptographic functions
//
// This file is part of Hexahedra.
//
// Hexahedra is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2014, nocte@hippie.nu
//---------------------------------------------------------------------------

#include "crypto.hpp"

#include <sstream>
#include <stdexcept>

#include <cryptopp/eccrypto.h>
#include <cryptopp/asn.h>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

namespace hexa {
    namespace crypto {

        static AutoSeededRandomPool rng;

        DL_PrivateKey_EC<ECP> make_new_key() {
            ECIES<ECP>::Decryptor decr(rng, ASN1::secp256k1());
            return decr.GetKey();
        }

        std::vector<uint8_t>
        make_random(int bytes) {
            if (bytes < 1)
                throw std::runtime_error("'bytes' must be greater than zero");

            std::vector<uint8_t> out(bytes);
            rng.GenerateBlock(&out[0], bytes);
            return out;
        }

        Integer
        make_random_128() {
            byte out[16];
            rng.GenerateBlock(out, 16);
            return Integer(out, 16);
        }

        std::string
        serialize_private_key(const DL_PrivateKey_EC<ECP>& key) {
            auto num(key.GetPrivateExponent());
            std::string result;
            HexEncoder enc(new StringSink(result));
            num.DEREncode(enc);
            //key.DEREncode(enc);

            return result;
        }

        DL_PrivateKey_EC<ECP>
        deserialize_private_key(const std::string& privkey) {
            throw 0;
        }

        std::string
        serialize_public_key(const DL_PrivateKey_EC<ECP>& privkey) {
            DL_PublicKey_EC<ECP> key;
            privkey.MakePublicKey(key);
            auto pt(key.GetPublicElement());

            std::string result;
            HexEncoder enc(new StringSink(result));
            key.GetGroupParameters().GetCurve().EncodePoint(enc, pt, true);

            return result;
        }

        DL_PublicKey_EC<ECP>
        deserialize_public_key(const std::string& privkey) {
            throw 0;
            /*
            Point pt;

            DL_PublicKey_EC<ECP> result;

            if (!result.Validate(rng, 3))
            {
                result.clear();
                throw std::runtime_error("Not a valid key");
            }

            return result;
             */
        }


    }
} // namespace hexa::crypto
