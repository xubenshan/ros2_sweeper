from setuptools import find_packages
from setuptools import setup

setup(
    name='oomwoo_localization_msgs',
    version='0.1.0',
    packages=find_packages(
        include=('oomwoo_localization_msgs', 'oomwoo_localization_msgs.*')),
)
