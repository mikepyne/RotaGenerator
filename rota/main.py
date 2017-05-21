import argparse
from .rota_days import RotaDays


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Do some rota magic')
    parser.add_argument('start', type=int, help="Starting month")
    parser.add_argument('end', type=int, help="Ending month")

    args = parser.parse_args()
    r = RotaDays()

    print(r.find_weekends(2017, args.start, args.end))
