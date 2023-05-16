import subprocess

red = "\033[31m"
green = "\033[32m"
reset = "\033[0m"

basicTest = [
   'hogehoge',
   '/bin/ls',
   'cat hoge.txt',
   'cat  hoge.txt',
   'cat\thoge.txt',
]

quoteCharacterTest = [
    "echo 'hogehoge'",
    'echo "hogehoge"',
    "echo 'hoge hoge'",
    'echo "hoge hoge"',
    "echo 'hoge\thoge'",
    'echo "hoge\thoge"',

    # unclosed
    # "echo 'hoge hoge",
    # 'echo "hoge hoge',
    # "echo hoge hoge'",
    # 'echo hoge hoge"',
    # "echo 'hoge' hoge'",
    # 'echo "hoge" hoge"',

    'echo "hogehoge" > out.txt',
    'echo "hogehoge" >> out.txt',
    'cat input.txt | grep ft',
    'cat input.txt | grep ft > out.txt',
    'cat input.txt | grep ft >> out.txt',
    '<input.txt cat | grep ft > out.txt',
    '<input.txt cat | grep ft >> out.txt',
    '<<EOF cat | grep ft > out.txt',
    '<<EOF cat | grep ft >> out.txt',
]


pipeRedirectionTest = [
   'cat hoge.txt | grep ft',
   'cat hoge.txt | grep ft > out.txt',
   'cat hoge.txt | grep ft >> out.txt',
   '<cat hoge.txt | grep ft out.txt',
   '<cat hoge.txt | grep ft > out.txt',
   '<cat hoge.txt | grep ft >> out.txt',
]

invalidInputTest = [
   r'echo "hoge hoge"',
   r"echo 'hoge'hoge'",
   'echo "hoge\'hoge"',
   r'echo "hoge\"hoge"',
]

operatorTest = [
    "cat test.txt > result.out",
    "cat test.txt | grep ft > result.out",
    "cat test.txt | grep ft >> result.out",
    "<test.txt cat | grep ft >> result.out",
    "<<EOF cat | grep ft >> result.out",
]

parserBasicTest = [
    # "/bin/ls",
    # '/bin/echo "hogehoge"',
    # "/bin/echo 'hogehoge'",
    '/bin/cat input.txt',
    '/bin/cat input.txt > out.txt',
    '/bin/cat input.txt | grep ft > out.txt',
    '<input.txt /bin/cat | grep ft > out.txt',

    '<cat hoge.txt | grep ft_ | grep ft  > out.txt',
]

def test_parser(inputStr):
    for i, input in enumerate(inputStr):
        command = ["./parser", input]
        runtest(i, command)

def runtest(index, command):
    res = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    print(f'===== TEST{index} =====')
    print('=== input ===')
    print(f"[{res.args[1]}]")
    print('=== stdout ===')
    print(f"{res.stdout.decode()}")
    print('=== stderr ===')
    print(f"{res.stderr.decode()}")

    if res.returncode == 0:
        print(f'===== TEST{index} {green} OK {reset} =====\n')
    else:
        print(f'===== TEST{index} {red} NG {reset} =====\n')

if __name__ ==  '__main__':
    # test_parser(basicTest)
    test_parser(quoteCharacterTest)
    # test_parser(pipeRedirectionTest)
    # test_parser(invalidInputTest)
    # test_parser(operatorTest)
    test_parser(parserBasicTest)
