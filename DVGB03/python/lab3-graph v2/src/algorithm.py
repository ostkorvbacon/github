#!/usr/bin/env python3

import sys
import logging
import copy

log = logging.getLogger(__name__)

from math import inf

def warshall(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Warshall's
    algorithm.

    Pre: adjlist is not empty.
    '''
    log.info("TODO: warshall()")
    return [[]]

def floyd(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Floyd's algorithm.

    Pre: adjlist is not empty.
    '''
    log.info("TODO: floyd()")
    return [[]]

def dijkstra(adjlist, start_node):
    '''
    Returns the result of running Dijkstra's algorithm as two N-length lists:
    1) distance d: here, d[i] contains the minimal cost to go from the node
    named `start_node` to the i:th node in the adjacency list.
    2) edges e: here, e[i] contains the node name that the i:th node's shortest
    path originated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: start_node is a member of adjlist.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 2
    b|* * 2
    c|* * *

    For start node "a", the expected output would then be:

    d: [ None, 1, 2]
    e: [ None, 'a', 'a' ]
    '''
    log.info("TODO: dijkstra()")
    d = []
    e = []
    return d, e



def prim(adjlist, start_node):
    '''
    Returns the result of running Prim's algorithm as two N-length lists:
    1) lowcost l: here, l[i] contains the weight of the cheapest edge to connect
    the i:th node to the minimal spanning tree that started at `start_node`.
    2) closest c: here, c[i] contains the node name that the i:th node's
    cheapest edge orignated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: adjlist is setup as an undirected graph and start_node is a member.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 3
    b|1 * 1
    c|3 1 *

    For start node "a", the expected output would then be:

    l: [ None, 1, 1]
    c: [ None, 'a', 'b' ]
    '''
    inf=999999999999
    l = []
    c = []
    q = []
    si=0
    n2=0
    n3=0
    first=True
    node=adjlist
    while node.name()!=None:
        l.append(inf)
        c.append(None)
        q.append(node)

        node=node.tail()

    q2=copy.deepcopy(q)
    l2=copy.deepcopy(l)


    i=0
    while i<len(q):
        if q[i].name()==start_node:
            si=i
            l[i]=0
            l2[i]=0

        i=i+1


    while len(q)!=0:

        n=l2.index(min_l(l2))

        u=q[n]
        v=u.edges()

        while v.dst()!=None:


            i=0

            while i<len(q):

                if v.dst()==q[i].name():
                    n2=find_dst(q[i].name(),q2)

                    if v.weight()<l[n2]:
                        l[n2]=v.weight()
                        n3=find_dst(q[i].name(),q)
                        l2[n3]=v.weight()

                        c[n2]=u.name()
                i=i+1

            v=v.tail()

        q.remove(u)

        l2.remove(l2[n])






    i=0
    while i<len(l):
        if l[i]==inf:
            l[i]=float('inf')
        i=i+1

    l[si]=None
    return l,c



def find_dst(name,q2):
    i=0

    while i<len(q2):
        if name==q2[i].name():

            return i

        i=i+1


def min_l(l):
    i=0
    m=inf
    while i<len(l):
        if l[i]<m:
            m=l[i]
        i=i+1

    return m

if __name__ == "__main__":
    logging.critical("module contains no main")
    sys.exit(1)
