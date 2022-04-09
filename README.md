# Stock-information-commands
This Linux based scripts and executables, can extract info on stocks you want from the internet from the Terminal
How it works:
from terminal, from within the folder you have downloaded this files into
you can use the command './get_stocks_data.sh XXX XXX XXXX ...' , by using this command the script will automatically download
and arrange in files (in a convenient format using greps, seds, awks, etc..) stocks of your choosing (up to 10 stocks for each script usage)
it will create the files as follows, for example for the stock AAPL:
the file AAPL.stock will be created containing stock statistics from the last ~20 years.
the file AAPL.eps will be created containing the stock's Earning-Per-Share from the last ~20 years.

The Makefile in this dir will create the following out files:
best_pe.o - arrange the stocks you chose in the script, by order of best average of eps from the last ~20 years.
EXAMPLE OF USAGE: './best_pe.o AAPL GOOG MSFT..' (the files of used stocks need to be in the dir from which the order has been executed via the Linux Terminal)
export_to_csv.o - will create a .csv file containing all the info downloaded of the stocks chosen.
EXAMPLE OF USAGE: './export_to_csv.o AAPL GOOG MSFT..' (the files of used stocks need to be in the dir from which the order has been executed via the Linux Terminal)
stockdata.c - will fetch into Terminal the requested information of a stock from a specified year
EXAMPLE OF USAGE: './stockdata.o –stockName <stock name> --yearData <year>' (the files of used stocks need to be in the dir from which the order has been executed via the Linux Terminal)
replace <stockName> with desired stock symbol of which you have downloaded info using the script, replace <year> with desired year.
  
NOTE: these executables and script have been designed to all be activated from the Linux Terminal.
