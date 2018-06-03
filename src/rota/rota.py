import logging
from collections import OrderedDict


class Rota:
    """Generate a readers' rota"""

    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.rota')
        self.masses = []

    def add_mass(self, mass):
        self.masses.append(mass)
