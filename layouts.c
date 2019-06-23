void
horizgrid(Monitor *m)
{
    unsigned int n, i;
    Client *c;
    // count windows
    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next) , n++);

    if (n == 0)
        return;

    else if (n == 1)
    { //just fill the whole screen
        c = nexttiled(m->clients);
        resize(c, m->wx, m->wy, m->ww - (2 * c->bw), m->wh - (2*c->bw), False);
    }
    else if (n == 2)
    { //split vertically
        
        int w = m->ww / 2;
        c = nexttiled(m->clients); //4th
        resize(c, m->wx, m->wy, w - (2*c->bw), m->wh - (2*c->bw), False);
        c = nexttiled(c->next);
        resize(c, m->wx + w, m->wy, w + (2*c->bw), m->wh - (2*c->bw), False);
    }
    else
    {
        int ntop = n/2;
        int nbottom = n - ntop;
        for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
        {
            if (i < ntop)
                resize(c, m->wx + i * m->ww / ntop, m->wy,
                        m->ww / ntop - (2*c->bw), m->wh / 2 - (2*c->bw), False);

            else
                resize(c, m->wx + (i - ntop) * m->ww / nbottom, m->wy + m->wh / 2,
                        m->ww / nbottom - (2*c->bw), m->wh / 2 - (2*c->bw), False);

        }
    }
}
