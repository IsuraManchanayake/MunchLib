import inspect
import time


def test_calculate_fruchterman_reingold_layout():
    import networkx as nx
    from munchlib.fruchterman import calculate_fruchterman_reingold_layout

    # Create a NetworkX graph
    G = nx.Graph()
    G.add_edge(1, 2)
    G.add_edge(2, 3)

    # Directly use the NetworkX graph object with the Cython function
    result = calculate_fruchterman_reingold_layout(G, speed=1, area=10000, gravity=10, iter=100)
    print(result)
    check = (result == [(5856.415361084446, 8340.49794343261), (8490.599268826549, 8384.600107049415), (6129.310269828168, 3778.0931618983454)])
    if check:
        print(f'Test {inspect.currentframe().f_code.co_name} passed')
    else:
        print(f'Test {inspect.currentframe().f_code.co_name} failed')


def test_calculate_ccm_coordination():
    from munchlib.ccm import calculate_ccm_coordination
    import skccm as ccm
    import numpy as np
    from skccm.utilities import train_test_split

    x1_path = 'data/ccm/x1.txt'
    x2_path = 'data/ccm/x2.txt'
    x1 = []
    x2 = []
    with open(x1_path, 'r') as inf:
        for line in inf:
            x1.append(float(line.strip()))
    with open(x2_path, 'r') as inf:
        for line in inf:
            x2.append(float(line.strip()))

    print(len(x1))
    t = time.time()
    sc1, sc2 = calculate_ccm_coordination(x1, x2, 10, 1, np.linspace(11, int(0.25 * len(x1)) + 1, dtype='int'))
    print('Time taken =', time.time() - t, 's')
    print(len(sc1), len(sc2))

    lag = 1
    embed = 10
    t = time.time()
    e1 = ccm.Embed(np.array(x1))
    X1 = e1.embed_vectors_1d(lag, embed)
    e2 = ccm.Embed(np.array(x2))
    X2 = e2.embed_vectors_1d(lag, embed)

    CCM = ccm.CCM()
    x1tr, x1te, x2tr, x2te = train_test_split(X1, X2, percent=.75)
    # 0714756022
    len_tr = len(x1tr)
    lib_lens = np.linspace(11, len(x1te), dtype='int')
    CCM.fit(x1tr,x2tr)
    x1p, x2p = CCM.predict(x1te, x2te,lib_lengths=lib_lens)
    sc1_py, sc2_py = CCM.score()
    print('Time taken =', time.time() - t, 's')

    print(np.linalg.norm(np.array(sc1) - np.array(sc1_py)))
    print(np.linalg.norm(np.array(sc2) - np.array(sc2_py)))
    print(np.array(sc1) - np.array(sc1_py))
    print(np.array(sc2) - np.array(sc2_py))


def main():
    # test_calculate_fruchterman_reingold_layout()
    test_calculate_ccm_coordination()


if __name__ == '__main__':
    main()
