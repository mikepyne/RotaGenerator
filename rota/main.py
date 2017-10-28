#!/usr/bin/env python3
import argparse
import os.path
import json
import logging
import logging.config
from collections import OrderedDict

from rota_days import RotaDays
from mass import Mass


# Logging configuration
LC = {
    "version": 1,
    "handlers": {
        "console": {
            "class": "logging.StreamHandler",
            "level": "INFO",
            "formatter": "screen",
            "stream": "ext://sys.stdout"
        },
        "file": {
            "class": "logging.FileHandler",
            "filename": "rota.log",
            "mode": "w",
            "level": "DEBUG",
            "formatter": "file"
        }
    },
    "formatters": {
        "screen": {
            "format": "%(asctime)s %(message)s",
            "datefmt": "%H:%M:%S"
        },
        "file": {
            "format": "%(asctime)s %(name)s %(levelname)s %(funcName)s %(message)s"
        }
    },
    "loggers": {
        "rotaGenerator": {
            "level": "DEBUG",
            "handlers": ["console", "file"]
        }
    }
}


if __name__ == '__main__':
    logging.config.dictConfig(LC)
    logger = logging.getLogger('rotaGenerator')

    logger.debug('=== Starting __main__')
    parser = argparse.ArgumentParser(description='Do some rota magic')
    parser.add_argument('start', type=int, help="Starting month")
    parser.add_argument('start_year', type=int, help="Starting year")
    parser.add_argument('end', type=int, help="Ending month")
    parser.add_argument('-e',
                        '--end_year',
                        type=int,
                        help="Ending year, if different",
                        nargs='?',
                        default=None)

    args = parser.parse_args()
    logger.debug('... Parsed arguments: %s', args)
    r = RotaDays()
    sundays = r.find_weekends(args.start_year, args.start, args.end,
                              args.end_year)

    try:
        config_fpath = os.path.join('/', 'home', 'mike', 'Projects',
                                    'RotaGenerator', 'config.json')

        logger.debug('... Opening config from %s', config_fpath)
        with open(config_fpath) as conf_file:
            loaded_data = json.load(conf_file, object_pairs_hook=OrderedDict)
            if len(loaded_data) is 0:
                raise ConfigError('No configuration details available')

            for index in loaded_data:
                m = Mass(index, loaded_data[index])

    except Exception as e:
        logger.error("Error reading JSON: '%s'", e)

    print('\n'.join(r.format_weekends(sundays)))
