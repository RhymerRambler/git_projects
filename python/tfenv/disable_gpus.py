try:
    tf.config.set_visible_devices([], 'GPU')
    visible_devices = tf.config.get_visible_devices()
    for device in visible_devices:
        assert device.device_type != 'GPU'
    print("======== Disabled the GPU's!!")
except:
    # Invalid device or cannot modify virtual
    # devices once initialized.
    pass
