// Copyright (c) 2004-present Facebook All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package resolver

import (
	"testing"
	"time"

	"github.com/AlekSi/pointer"
	"github.com/facebookincubator/symphony/graph/ent/user"
	"github.com/facebookincubator/symphony/graph/graphql/models"
	"github.com/facebookincubator/symphony/graph/viewer"
	"github.com/facebookincubator/symphony/graph/viewer/viewertest"
	"github.com/google/uuid"
	"github.com/stretchr/testify/require"
)

func toStatusPointer(status user.Status) *user.Status {
	return &status
}

func TestEditUser(t *testing.T) {
	r := newTestResolver(t)
	defer r.drv.Close()
	ctx := viewertest.NewContext(r.client)
	prepareUserData(t, ctx, r.client)

	u, err := viewer.UserFromContext(ctx)
	require.NoError(t, err)
	require.Equal(t, user.StatusActive, u.Status)
	require.Empty(t, u.FirstName)

	mr := r.Mutation()
	u, err = mr.EditUser(ctx, models.EditUserInput{ID: u.ID, Status: toStatusPointer(user.StatusDeactivated), FirstName: pointer.ToString("John")})
	require.NoError(t, err)
	require.Equal(t, user.StatusDeactivated, u.Status)
	require.Equal(t, "John", u.FirstName)
}

func TestAddAndDeleteProfileImage(t *testing.T) {
	r := newTestResolver(t)
	defer r.drv.Close()
	ctx := viewertest.NewContext(r.client)
	prepareUserData(t, ctx, r.client)
	u, err := viewer.UserFromContext(ctx)
	require.NoError(t, err)

	mr, ur := r.Mutation(), r.User()
	now := time.Now()
	file1, err := mr.AddImage(ctx, models.AddImageInput{
		EntityType:  models.ImageEntityUser,
		EntityID:    u.ID,
		ImgKey:      uuid.New().String(),
		FileName:    "profile_photo.png",
		FileSize:    123,
		Modified:    now,
		ContentType: "image/png",
		Category:    nil,
	})
	file, err := ur.ProfilePhoto(ctx, u)
	require.NoError(t, err)
	require.Equal(t, "profile_photo.png", file.Name)

	_, err = mr.DeleteImage(ctx, models.ImageEntityUser, u.ID, file1.ID)
	require.NoError(t, err)

	file, err = ur.ProfilePhoto(ctx, u)
	require.NoError(t, err)
	require.Nil(t, file)
}
