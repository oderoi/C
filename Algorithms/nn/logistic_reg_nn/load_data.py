import numpy as np
import h5py

def load_dataset():
    trn_data=h5py.File('/datasets/train_catvnoncat.h5', "r")
    trn_set_x=np.array(trn_data["train_set_x"][:])
    trn_set_y=np.array(trn_data["train_set_y"][:])

    test_data=h5py.File('/datasets/test_catvnoncat.h5', "r")
    test_set_x=np.array(test_data["test_set_x"][:])
    test_set_y=np.array(test_data["test_set_y"][:])

    classes=np.array(test_data["list_classes"][:])

    trn_set_y=trn_set_y.reshape((1, trn_set_y.shape[0]))
    test_set_y=test_set_y((1, test_set_y.shape[0]))

    return trn_set_x, trn_set_y, test_set_x, test_set_y, classes