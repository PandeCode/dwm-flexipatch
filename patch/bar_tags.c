int
width_tags(Bar *bar, BarWidthArg *a)
{
	int w, i;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		occ |= c->tags == 255 ? 0 : c->tags;
	#endif // BAR_HIDEVACANTTAGS_PATCH

	for (w = 0, i = 0; i < LENGTH(tags); i++) {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		#if BAR_ALTERNATIVE_TAGS_PATCH
		w += selmon->alttag ? TEXTW(tagsalt[i]) : TEXTW(tags[i]);
		#else
		w += TEXTW(tags[i]);
		#endif // BAR_ALTERNATIVE_TAGS_PATCH
	}
	return w;
}

int
draw_tags(Bar *bar, BarDrawArg *a)
{
	int invert;
	int w, x = a->x;
	#if BAR_ALTERNATIVE_TAGS_PATCH
	int wdelta;
	#endif // BAR_ALTERNATIVE_TAGS_PATCH
	unsigned int i, occ = 0, urg = 0;
	Client *c;
	Monitor *m = bar->mon;

	for (c = m->clients; c; c = c->next) {
		#if BAR_HIDEVACANTTAGS_PATCH
		occ |= c->tags == 255 ? 0 : c->tags;
		#else
		occ |= c->tags;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		if (c->isurgent)
			urg |= c->tags;
	}

	for (i = 0; i < LENGTH(tags); i++) {
		#if BAR_HIDEVACANTTAGS_PATCH
		/* do not draw vacant tags */
		if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		invert = 0;
		w = TEXTW(tags[i]);
		#if BAR_ALTERNATIVE_TAGS_PATCH
		wdelta = selmon->alttag ? abs(TEXTW(tags[i]) - TEXTW(tagsalt[i])) / 2 : 0;
		#endif // BAR_ALTERNATIVE_TAGS_PATCH
		drw_setscheme(drw, scheme[
			m->tagset[m->seltags] & 1 << i
			? SchemeTagsSel
			: urg & 1 << i
			? SchemeUrg
			: SchemeTagsNorm
		]);
		#if BAR_ALTERNATIVE_TAGS_PATCH
		drw_text(drw, x, 0, w, bh, wdelta + lrpad / 2, (selmon->alttag ? tagsalt[i] : tags[i]), invert, False);
		#else
		drw_text(drw, x, 0, w, bh, lrpad / 2, tags[i], invert, False);
		#endif // BAR_ALTERNATIVE_TAGS_PATCH
		drawindicator(m, NULL, occ, x, w, i, -1, invert, tagindicatortype);
		x += w;
	}

	return 1;
}

int
click_tags(Bar *bar, Arg *arg, BarClickArg *a)
{
	int i = 0, x = lrpad / 2;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		occ |= c->tags == 255 ? 0 : c->tags;
	#endif // BAR_HIDEVACANTTAGS_PATCH

	do {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		#if BAR_ALTERNATIVE_TAGS_PATCH
		x += selmon->alttag ? TEXTW(tagsalt[i]) : TEXTW(tags[i]);
		#else
		x += TEXTW(tags[i]);
		#endif
	} while (a->rel_x >= x && ++i < LENGTH(tags));
	if (i < LENGTH(tags)) {
		arg->ui = 1 << i;
	}
	return ClkTagBar;
}