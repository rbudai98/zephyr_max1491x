.. zephyr:code-sample:: max14916
   :name: Max14916

   Print "Max14916" to the console.

Overview
********

A simple sample that can be used with any :ref:`supported board <boards>` 

Building and Running
********************

This application can be built and executed on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: samples/max14916
   :host-os: unix
   :board: qemu_x86
   :goals: run
   :compact:

To build for another board, change "qemu_x86" above to that board's name.

Sample Output
=============

.. code-block:: console

    Max14916 x86

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.
