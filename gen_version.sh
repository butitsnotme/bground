#!/bin/bash


# Create version file
VERSION="$(git describe --tags $(git rev-list --tags='v[0-9].[0-9]*' --max-count=1))"
VERSION=${VERSION#v}
REV="$(git rev-list --all --max-count=1)"
DATE=`date '+%Y-%m-%d %H:%M'`

# Check to see if we have a CI provided branch value
if [[ -z $BRANCH_NAME ]]
then
  BRANCH="$(git symbolic-ref HEAD 2> /dev/null || echo "(unnamed branch)")" # detached HEAD
  BRANCH=${BRANCH##refs/heads/}
else
  BRANCH="${BRANCH_NAME##*/}"
fi

if [[ $BRANCH == release* ]] || [[ $BRANCH == "master" ]]
then
  ON_RELEASE_BRANCH="true"
else
  ON_RELEASE_BRANCH="false"
fi

if [[ -z $NODE_NAME ]]
then
  WHO="`whoami`@`hostname`" 
else
  WHO="Jenkins ($NODE_NAME)"
fi

echo "$VERSION" > data/VERSION
echo "$REV" >> data/VERSION
echo "$BRANCH" >> data/VERSION
echo "$WHO" >> data/VERSION
echo "$DATE" >> data/VERSION
