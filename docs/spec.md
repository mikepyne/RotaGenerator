# Objective

Automate filling in a readers' rota.

# Data Output

The table format in the manually produced rotas comprises three columns:

* Weekend; two lines similar to:

  Saturday 22nd/Sunday 23rd September
  22nd Sunday in Ordinary Time

* Saturday; shows the readers for the Saturday Mass

  Each Saturday cell contains two rows, one for each reader

* Sunday; shows the readers for the Sunday Mass

  Each Sunday cell contains three rows, one for each reader

# Processing Rules

* Most readers read at the same mass (i.e. either on Saturday or Sunday.)
* Some readers read at both masses
  * A reader should not be assigned to read at both masses on the same weekend
* Saturday mass needs two readers
* Sunday mass needs three readers
* Some readers may always read togther (e.g. families)

# Manual Process

1. Find dates and liturgical occasion each weekend in the rota; this is used to
   populate the Weekend column (see the Data Output section).
2. Ignore/blank any excluded services (e.g. First Holy Communion mass).
2. Fill in readers for Saturday; the first reader will be the next one after the
   end of the last rota.
3. Fill in readers for Sunday; the first reader will also be next one after the
   end of the last rota.
4. Make sure any individual exclusions (i.e. a reader has told me they aren't
   available on a particular date) are okay; revise, if necessary.
5. Make sure any Saturday and Sunday readers aren't assigned to both masses on
   the same weekend.

# Automating the Process

To start with, the automated process can follow the manual process. The first
step, therefore, is getting the dates and liturgical details for each weekend.
