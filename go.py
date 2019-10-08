import subprocess
import os
import shutil
import glob
import time
import argparse
import errno
import group_exec
import findpeaksG_py
import ims_extractor
import multiprocessing


def fit_eachname(eachname):
    path = os.getcwd()
    dir_name = eachname.split('.')[0]
    ims = eachname + '.ims'
    os.chdir(dir_name)
    if not os.path.isfile('result.res'):
        findpeaksG_py.fit_gauss('mass_data.dilu', 'result.res')

        # exe_line = ["..\\pypy findpeaksG_py.py mass_data.dilu result.res"]
        # print exe_line
        # p = subprocess.Popen(exe_line)
        os.chdir(path)
        # p.communicate()
    else:
        print "result.res exist!"
    return ims


def copytree2(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)


def copy(src, dest):
    try:
        copytree2(src, dest)
    except OSError as e:
        # If the error was caused because the source wasn't a directory
        if e.errno == errno.ENOTDIR:
            shutil.copy(src, dest)
        else:
            print('Directory not copied. Error: %s' % e)


if __name__ == '__main__':
    CPU_NUM = 4
    tic_corr_method = 2  # default=2, 1=global tic correction 2=group tic correction 3=no correction
    file_list = []
    own_path = os.path.dirname(os.path.realpath(__file__))

    print "usage: python go.py --input [filename 1] [filename2] ... --corr [1/2/3] (1:global tic correction, 2: group tic correction, 3: no correction --output [path]  --ret_corr [0 0 0 0 0 0] --tic_corr [1 1 1 1 1 1]"

    parser = argparse.ArgumentParser()
    parser.add_argument('--input', nargs='*')
    parser.add_argument('--corr', nargs=1)
    parser.add_argument('--output', nargs=1)
    parser.add_argument('--ret_corr', nargs='*')
    parser.add_argument('--tic_corr', nargs='*')
    parser.add_argument('--database', nargs='*')

    args = parser.parse_args()
    # args is Namespace(details=['asdf', 'a', 'a'], quickly=False, t='4', v=True)
    file_list = args.input
    tic_corr_method = int(args.corr[0])
    output_dir = str(args.output[0])
    database_file = str(args.database[0])
    database_ppm_tolerance = float(args.database[1])
    database_search_mode = str(args.database[2])
    ret_corr = [float(ret) for ret in args.ret_corr]
    tic = [float(tic_temp) for tic_temp in args.tic_corr]

    num_of_files = len(file_list)

    print own_path, output_dir, num_of_files

    copy(own_path, output_dir)
    os.chdir(output_dir)

    for eachname in file_list:
        dir_name = output_dir + '/' + os.path.basename(eachname).split('.')[0]
        try:
            os.stat(dir_name)
        except:
            os.mkdir(dir_name)
    pool = multiprocessing.Pool(processes=CPU_NUM)
    pool.map(ims_extractor.extract_file, file_list)
    pool.close()
    pool.join()

    # exe_line = ["E:\\Python\\pypy2-v5.6.0-win32\\pypy.exe", "ims_extractor.py", eachname]
    # p = subprocess.Popen(exe_line)
    # p.communicate()

    tic_corr = []
    for eachname in file_list:
        ims = eachname + '.ims'
        dir_name = eachname.split('.')[0]
        my_path = os.path.abspath(__file__)
        mydir = os.path.dirname(my_path)
        # start = os.path.join(mydir, "move")
        dir_name = os.path.join(mydir, dir_name)
        ims_exist = dir_name + '\\' + ims.split('\\')[-1]
        ims = os.path.join(mydir, ims)
        print dir_name, ims_exist, ims
        if not os.path.isfile(ims_exist):
            shutil.move(ims, dir_name)
        common = os.path.join(mydir, "common")
        for filename in glob.glob(os.path.join(common, '*.*')):
            shutil.copy(filename, dir_name)
        freq_name = dir_name + "_frequency.csv"
        with open(freq_name) as f:
            for line in f:
                if line[0] == 'T':
                    a = float(line.split(' ')[1])
                    tic_corr.append(a)

    if tic_corr_method == 2:
        tic = []
        tic_min1 = min(tic_corr[0:num_of_files / 2])
        tic_min2 = min(tic_corr[num_of_files / 2:num_of_files])

        for number in tic_corr[0:num_of_files / 2]:
            tic_coef = 10 ** (tic_min1 - number)
            tic.append(tic_coef)
            print tic_coef

        for number in tic_corr[num_of_files / 2:num_of_files]:
            tic_coef = 10 ** (tic_min2 - number)
            tic.append(tic_coef)
            print tic_coef

    elif tic_corr_method == 1:
        tic = []
        tic_min = min(tic_corr)

        for number in tic_corr:
            tic_coef = 10 ** (tic_min - number)
            tic.append(tic_coef)
            print tic_coef
    else:
        if len(tic) != num_of_files:
            tic = [1] * num_of_files

    i = 0
    for eachname in file_list:
        path = os.getcwd()
        dir_name = eachname.split('.')[0]
        ims = os.path.basename(eachname) + '.ims'
        os.chdir(dir_name)
        if not os.path.isfile('mass_data.dilu'):
            exe_line = 'dilu_c_onefile.exe ' + ims + ' ' + str(tic[i])
            print exe_line
            p = subprocess.Popen(exe_line)
        else:
            print "mass_data.dilu exist!"
        i += 1
        os.chdir(path)
    p.communicate()

    not_done = 0
    while not_done != len(file_list):
        not_done = 0
        for eachname in file_list:
            dir_name = eachname.split('.')[0]
            done_file = os.listdir(dir_name)
            if 'done.dilu' in done_file:
                not_done += 1
            else:
                not_done = 0
        time.sleep(10)

    with open('tic.log', 'w') as tic_log_file:
        for each in tic:
            tic_log_file.write(str(each) + '\n')
    '''
    pool=multiprocessing.Pool(processes=CPU_NUM)
    ims_array=pool.map(fit_eachname,file_list)
    pool.close()
    pool.join()
    '''
    for eachname in file_list:
        path = os.getcwd()
        dir_name = eachname.split('.')[0]
        ims = eachname + '.ims'
        os.chdir(dir_name)
        if not os.path.isfile('result.res'):
            findpeaksG_py.fit_gauss('mass_data.dilu', 'result.res')

            # exe_line = ["..\\pypy findpeaksG_py.py mass_data.dilu result.res"]
            # print exe_line
            # p = subprocess.Popen(exe_line)
            os.chdir(path)
            # p.communicate()
        else:
            print "result.res exist!"

    print "Done importing data..."

    not_done = 0
    while not_done != len(file_list):
        not_done = 0
        for eachname in file_list:
            dir_name = eachname.split('.')[0]
            done_file = os.listdir(dir_name)
            if 'done.res' in done_file:
                not_done += 1
            else:
                not_done = 0
        time.sleep(10)

    result_array = []

    for eachname in file_list:
        dir_name = eachname.split('.')[0]
        result_file = dir_name + '\\result.res'
        result_array.append(result_file)
    print output_dir, result_array, file_list, map(str, range(1, num_of_files + 1)), map(str, range(1,
                                                                                                    num_of_files + 1)), 5, ret_corr, tic, 'result.csv', 'lmsd.tsv', 15, database_search_mode, 0.05, 2
    group_exec.group_all(output_dir, result_array, file_list, map(str, range(1, num_of_files + 1)),
                         map(str, range(1, num_of_files + 1)), 5, ret_corr, tic, 'result.csv', 'lmsd.tsv', 15,
                         database_search_mode, 0.05, 2)

    '''
    os.chdir(output_dir)
    exe_line = 'python group.py --result ' + ' '.join(result_array) + ' --ms1 ' + ' '.join(file_list) +
    ' --group1 ' + ' '.join(map(str, range(1, num_of_files + 1))) +
    ' --group2 ' + ' '.join(map(str, range(1, num_of_files + 1))) + ' --ppm 5 --ret_corr ' + ' '.join(
        map(str, ret_corr)) + ' --int_corr ' + ' '.join(map(str, tic)) + ' --output result.csv --database lmsd.tsv 15 '+database_search_mode+ ' --pic_pvalue 0.05 --pic_fold 2'
    print exe_line
    p = subprocess.Popen(exe_line)
    p.communicate()
    '''
    print "All finished!"
