import logging
from collections import OrderedDict


class Rota:
    """Generate a readers' rota"""

    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.rota')

    def assign_readers(self, num_days, config_data):
        """Assign readers for a number of days

        Parameters:
        num_days -- the number of days
        config_data -- Contains the number of spaces, list of readers, etc.
        """
        assignments = OrderedDict()
        reader_index = config_data['startfrom']
        # needed = config_data['needed']
        for i in range(num_days):
            names = config_data['readers'][reader_index]

            assignments[str(i + 1)] = names['name']
            reader_index += 1

        return assignments
