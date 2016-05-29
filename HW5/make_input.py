import msgpack

f_in = open('input.txt','wb')

tests = [
    '1 + 3  *4   ',
    '  3  + 4*  1',
    '   1+2+3+4   ',
    ' 1 * 3 + 4 - 4 * 1',
    '1-2*3*4+4+1'
]
num_test = len(tests)

f_in.write(msgpack.packb(num_test))
for test in tests:
    f_in.write(msgpack.packb(test))

f_out = open('sample_output.txt','wb')
ans = [
    2,
    1,
    1,
    1,
    18
]

for a in ans:
    f_out.write(msgpack.packb(a))


