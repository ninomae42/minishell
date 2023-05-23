import subprocess

red = "\033[31m"
green = "\033[32m"
reset = "\033[0m"

def test_parser(inputStr):
    for i, input in enumerate(inputStr):
        command = ["./minishell", input]
        runtest(i, command)

def runtest(index, command):
    res = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    print(f'===== TEST{index} =====')
    print('=== input ===')
    print(f"[{res.args[1]}]")
    print('=== stdout ===')
    print(f"{res.stdout.decode()}")
    # print('=== stderr ===')
    # print(f"{res.stderr.decode()}")

    if res.returncode == 0:
        print(f'===== TEST{index} {green} OK {reset} ({res.returncode}) =====\n')
    else:
        print(f'===== TEST{index} {red} NG {reset} ({res.returncode}) =====\n')

basicTest = [
    '/bin/ls',
    '/bin/echo',
    '/bin/echo hello',
    '/bin/echo hello world',
    '/bin/echo hello world hoge',
    '/bin/echo hello world hoge moge',
]

if __name__ ==  '__main__':
    test_parser(basicTest)
