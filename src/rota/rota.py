import logging
from collections import OrderedDict


class Rota:
    """Generate a readers' rota"""

    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.rota')

    def assign_readers(self, count, config_data):
        """Assign readers for a number of days

        Parameters:
        count -- the number of days
        config_data -- Contains the number of spaces, list of readers, etc.
        """
        assignments = OrderedDict()
        reader_index = config_data['startfrom']
        spaces_filled = 0
        for i in range(count):
            names = config_data['readers'][reader_index]

            if len(names) > config_data['needed']:
                self.logger.warn("Reader %s has more names than spaces (%s)",
                                 reader_index,
                                 config_data['needed'])
            elif len(names) == config_data['needed']:
                assignments.append(i + 1, names)
                reader_index += 1
            else:
                pass
