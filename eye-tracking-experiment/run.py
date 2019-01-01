from Experiment import Experiment
import logging
import sys
import argparse

def set_log_format():
    logging.basicConfig(level=logging.DEBUG,
                        format='%(threadName)-12s %(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S',
                        filename='experiment.log',
                        filemode='a')

    console = logging.StreamHandler(sys.stdout)
    console.setLevel(logging.INFO)
    formatter = logging.Formatter('%(filename)-12s line:%(lineno)d: %(levelname)-8s %(message)s')
    console.setFormatter(formatter)
    logging.getLogger('').addHandler(console)

    console_err = logging.StreamHandler(sys.stderr)
    console_err.setLevel(logging.ERROR)
    formatter = logging.Formatter('%(filename)-12s line:%(lineno)d: %(levelname)-8s %(message)s')
    console_err.setFormatter(formatter)
    logging.getLogger('').addHandler(console_err)

def main():
    parser = argparse.ArgumentParser(description="Assign task for a user based on the data in DB.")
    parser.add_argument("-i", "--fromi", type=int, help="continue from i th video", default=0)
    parser.add_argument("-m", "--male", type=bool, help="whether the user is male", default=True)
    parser.add_argument("-a", "--age", type=int, help="user age", default=20)
    parser.add_argument("name", type=str, help="user name")
    args = parser.parse_args()

    set_log_format()
    exp = Experiment()
    exp.start_from_i(args.fromi, args.name, args.male, args.age)

if __name__ == '__main__':
    main()