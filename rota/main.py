import argparse
import os.path
import json
import logging
import logging.config
from .rota_days import RotaDays
from .config import Config, ConfigException


if __name__ == '__main__':
    with open(os.path.join('/', 'home', 'mike', 'Projects',
                           'RotaGenerator', 'log_config.json')) as lcf:
        lc = json.load(lcf)
        logging.config.dictConfig(lc)

    logger = logging.getLogger('rotaGenerator')

    logger.debug('=== Starting __main__')
    parser = argparse.ArgumentParser(description='Do some rota magic')
    parser.add_argument('start', type=int, help="Starting month")
    parser.add_argument('start_year', type=int, help="Starting year")
    parser.add_argument('end', type=int, help="Ending month")
    parser.add_argument('-e', '--end_year', type=int, help="Ending month, if different",
                        nargs='?', default=None)

    args = parser.parse_args()
    logger.debug('... Parsed arguments: %s', args)
    r = RotaDays()
    config = Config()

    try:
        config_fpath = os.path.join('/', 'home', 'mike', 'Projects',
                                    'RotaGenerator', 'config.json')

        logger.debug('... Opening config from %s', config_fpath)
        with open(config_fpath) as conf_file:
            config.read(conf_file)

    except ConfigException as e:
        print ('Error: {0}'.format(e.msg))

    print('\n'.join(r.find_weekends(args.start_year, args.start, args.end,
                                    args.end_year)))
