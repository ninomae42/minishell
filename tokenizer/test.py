import subprocess

metacharTest = [
        '', ' ', '\t', '\n', '|', '&', ';',
        '(', ')', '<', '>', "'", '"', "''", '""',
]

basicTest = [
        'hogehoge',
        '/bin/ls',
        'cat hoge.txt',
        'cat  hoge.txt',
        'cat\thoge.txt',
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

quoteCharacterTest = [
    "echo 'hogehoge'",
    'echo "hogehoge"',
    'echo "hogehoge" >> out.txt',
]

def test_tokenizer(inputStr):
    for i, input in enumerate(inputStr):
        command = ["./tokenizer", input]
        runtest(i, command)

def runtest(index, command):
    res = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    print(f'===== TEST{index} =====')
    print(f"command:[{res.args[1]}]")
    # print(f"exit status {res.returncode}")
    print(f"stdout {res.stdout.decode()}")
    print(f"stderr {res.stderr.decode()}")

    if res.returncode == 0:
        print(f'===== OK =====\n')
    else:
        print(f'===== NG =====\n')

if __name__ ==  '__main__':
    # test_tokenizer(metacharTest)
    # test_tokenizer(basicTest)
    # test_tokenizer(pipeRedirectionTest)
    # test_tokenizer(invalidInputTest)
    # test_tokenizer(operatorTest)
    test_tokenizer(quoteCharacterTest)
