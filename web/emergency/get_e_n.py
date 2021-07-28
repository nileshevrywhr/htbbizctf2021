from Crypto.PublicKey import RSA

fp = open("publickey.crt" ,"r")
key = RSA.importKey(fp.read())
fp.close()

print("n: ", key.n)
print("e: ", key.e)
