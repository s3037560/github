node('master') 
{
    stage('Checkout')
    {
    checkout([$class: 'GitSCM', branches: [[name: '*/master']], browser: [$class: 'GithubWeb', repoUrl: 'https://github.com/s3037560/github'], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: '']], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/s3037560/github']]])
    }
    stage('Publish Perforce')
    {
    p4publish credential: 'master', publish: submit(delete: true, description: 'Submitted by Jenkins. Build: ${BUILD_TAG}', onlyOnSuccess: false, purge: '', reopen: false), workspace: manualSpec(charset: 'utf8', name: 'jenkins-${NODE_NAME}-${JOB_NAME}-${EXECUTOR_NUMBER}', pinHost: false, spec: clientSpec(allwrite: true, backup: false, clobber: false, compress: false, line: 'LOCAL', locked: true, modtime: false, rmdir: true, serverID: '', streamName: '', type: 'WRITABLE', view: '//depot/... //jenkins-${NODE_NAME}-${JOB_NAME}-${EXECUTOR_NUMBER}/...'))
    }
}
    
