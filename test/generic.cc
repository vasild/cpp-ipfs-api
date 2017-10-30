/* Copyright (c) 2016-2016, Vasil Dimov

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <ipfs/client.h>
#include <ipfs/test/utils.h>

int main(int, char**) {
  try {
    /** [ipfs::Client::Client] */
    ipfs::Client client("localhost", 5001);
    /** [ipfs::Client::Client] */

    /** [ipfs::Client::Id] */
    ipfs::Json id;
    client.Id(&id);
    std::cout << "Peer's public key: " << id["PublicKey"] << std::endl;
    /* An example output:
    Peer's public key: "CAASpgIwggEiMA0GCSqGSIb3DQN/ImJDE/CN1eHE....gMBAAE="
    */
    /** [ipfs::Client::Id] */
    ipfs::test::check_if_properties_exist("client.Id()", id,
                                          {"Addresses", "ID", "PublicKey"});

    /** [ipfs::Client::Version] */
    ipfs::Json version;
    client.Version(&version);
    std::cout << "Peer's version: " << version << std::endl;
    /* An example output:
    Peer's version: {"Commit":"ee6dd5e","Golang":"go1.7.3","Repo":"4",
    "System":"amd64/freebsd","Version":"0.4.3"}
    */
    /** [ipfs::Client::Version] */
    ipfs::test::check_if_properties_exist("client.Version()", version,
                                          {"Repo", "System", "Version"});

    /** [ipfs::Client::Get] */
    std::stringstream contents;
    client.Get(
        "/ipfs/QmYwAPJzv5CZsnA625s3Xf2nemtYgPpHdWEz79ojWnPbdG/readme",
        &contents);
    /* An example output:
     * readme */
    std::cout << contents.str().substr(0, 20) << std::endl;
    /** [ipfs::Client::Get] */
    ipfs::test::check_if_string_contains("client.get()", contents.str(),
        "Hello and Welcome to IPFS!");

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
