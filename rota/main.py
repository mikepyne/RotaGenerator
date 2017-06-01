import argparse
import os.path
from .rota_days import RotaDays
from .config import Config, ConfigException


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Do some rota magic')
    parser.add_argument('start', type=int, help="Starting month")
    parser.add_argument('end', type=int, help="Ending month")

    args = parser.parse_args()
    r = RotaDays()

    config = Config()
    try:
        with open(os.path.join('/', 'home', 'mike', 'Projects', 'RotaGenerator',
                               'config.json')) as conf_file:

            config.read(conf_file)

    except ConfigException as e:
        print ('Error: {0}'.format(e.msg))

    print('\n'.join(r.find_weekends(2017, args.start, args.end)))
