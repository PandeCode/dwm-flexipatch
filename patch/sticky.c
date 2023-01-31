void
togglesticky(const Arg *arg)
{
	if (!selmon->sel)
		return;
	selmon->sel->issticky = !selmon->sel->issticky;
	arrange(selmon);
}

void
setsticky(const Arg *arg)
{
	if (!selmon->sel)
		return;
	selmon->sel->issticky = 1;
	arrange(selmon);
}

void
unsetsticky(const Arg *arg)
{
	if (!selmon->sel)
		return;
	selmon->sel->issticky = 0;
	arrange(selmon);
}

