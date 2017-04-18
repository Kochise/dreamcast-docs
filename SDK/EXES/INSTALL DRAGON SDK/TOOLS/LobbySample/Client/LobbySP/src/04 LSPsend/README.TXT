Welcome to the Windows CE Toolkit for Dreamcast!

To facilitate remote debugging, go to the "WCE Configuration" toolbar and
select the "Dreamcast" configuration, if it is not already selected. Then,
open the "Project Settings" dialog by selecting "Project" then "Settings..."
from the Menu Bar. In the "Settings For:" dropdown listbox at the left of the
"Project Settings" dialog, select "All Configurations". Find and select the
"Post-build step" tab at the right of the "Project Settings" dialog (you may
need to scroll through the tabs until it is visible). In the "Post-build
description:" field, enter:

Copying executable to the release directory.

In the "Post-build command(s):" area, click on the highlighted entry and
enter:

dccopy $(TargetPath)
