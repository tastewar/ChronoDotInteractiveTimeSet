# ChronoDotInteractiveTimeSet
sketch to interactively set the time on a ChronoDot
This sketch can be uploaded to an Arduino or compatible and run interactively via Serial Monitor,
and it will prompt for all the DateTime fields and after user's confirmation, will set the clock.

I wrote this out of frustration with the usual method, which does a one time set of the time based
on the compilation timestamp, which seems only approximate and very final.

So for a project that doesn't offer a UI to set the clock, you can upload this sketch (temporarily),
set the time, then upload the original sketch, with any time setting code removed.
